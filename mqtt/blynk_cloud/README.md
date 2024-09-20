## Blynk.Cloud的MQTT Bloker
### 1. 工作流程
- step1. **Developer Zone -> My Templates**
- step2. **Device**

### 2. [使用內建的tutorial範例(github)](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples)

利用Blynk.Cloud內建的 **MQTT Air Cooler/Heater** Blueprints

 - 2.1 **在Blynk.Cloud的設定**

	1. Create Blynk template based on the provided blueprint. Click the **`Use Blueprint`** button in [`MQTT Air Cooler/Heater Demo`](https://blynk.cloud/dashboard/blueprints/Library/TMPL4zGiS1A7l).
	2. In the left panel, select `Devices`
	3. Click `New Device` button
	4. Select `From Template -> MQTT Demo`, and click **`Create`**

- 2.2 **安裝python套件**

```
pip3 install --upgrade paho-mqtt
```

- 2.3 **建立config.py**
連線雲端的設定

```
# Fill in information from Blynk Device Info here.
BLYNK_TEMPLATE_ID   = ""
BLYNK_TEMPLATE_NAME = ""
BLYNK_AUTH_TOKEN    = ""

# Change the default Blynk server. Applicable for users with a white label plan.
BLYNK_MQTT_BROKER   = "blynk.cloud"
```

- 2.4 **demo.py**
程式模擬heater裝置

```
# SPDX-FileCopyrightText: 2024 Volodymyr Shymanskyy for Blynk Technologies Inc.
# SPDX-License-Identifier: Apache-2.0
#
# The software is provided "as is", without any warranties or guarantees (explicit or implied).
# This includes no assurances about being fit for any specific purpose.

import random

LOGO = r"""
      ___  __          __
     / _ )/ /_ _____  / /__
    / _  / / // / _ \/  '_/
   /____/_/\_, /_//_/_/\_\
          /___/
"""

class Device:
    power_on = False
    target_temp = 23    # Target temperature, can be set from 10 to 30
    current_temp = 15   # Initial current temperature

    def __init__(self, mqtt):
        self.mqtt = mqtt

    def connected(self):
        # Get latest settings from Blynk.Cloud
        self.mqtt.publish("get/ds", "Power,Set Temperature")

        # Display Blynk logo, just for fun
        self.terminal_print(LOGO)
        self.terminal_print("Type \"help\" for the list of available commands")

    def terminal_print(self, *args):
        self.mqtt.publish("ds/Terminal", " ".join(map(str, args)) + "\n")

    def process_message(self, topic, payload):
        if topic == "downlink/ds/Power":
            self.power_on = bool(int(payload))
            settemp_disabled = 0 if self.power_on else 1
            self.mqtt.publish("ds/Set Temperature/prop/isDisabled", settemp_disabled)
        elif topic == "downlink/ds/Set Temperature":
            self.target_temp = float(payload)
        elif topic == "downlink/ds/Terminal":
            cmd = list(filter(len, payload.split()))
            if cmd[0] == "set":
                self.target_temp = int(cmd[1])
                self.mqtt.publish("ds/Set Temperature", self.target_temp)
                self.terminal_print(f"Temperature set to {self.target_temp}")
            elif cmd[0] == "on":
                self.power_on = True
                self.mqtt.publish("ds/Power", 1)
                self.terminal_print("Turned ON")
            elif cmd[0] == "off":
                self.power_on = False
                self.mqtt.publish("ds/Power", 0)
                self.terminal_print("Turned OFF")
            elif cmd[0] in ("help", "?"):
                self.terminal_print("Available commands:")
                self.terminal_print("  set N    - set target temperature")
                self.terminal_print("  on       - turn on")
                self.terminal_print("  off      - turn off")
            else:
                self.terminal_print(f"Unknown command: {cmd[0]}")

    def _update_temperature(self):
        target = self.target_temp if self.power_on else 10
        next_temp = self.current_temp + (target - self.current_temp) * 0.05
        next_temp = max(10, min(next_temp, 35))
        next_temp += (0.5 - random.uniform(0, 1)) * 0.3
        self.current_temp = next_temp
        self.mqtt.publish("ds/Current Temperature", self.current_temp)

    def _update_widget_state(self):
        if not self.power_on:
            state = 1 # OFF
        elif abs(self.current_temp - self.target_temp) < 1.0:
            state = 2 # Idle
        elif self.target_temp > self.current_temp:
            state = 3 # Heating
        elif self.target_temp < self.current_temp:
            state = 4 # Cooling

        state_colors = [None, "E4F6F7", "E6F7E4", "F7EAE4", "E4EDF7"]
        self.mqtt.publish("ds/Status", state)
        self.mqtt.publish("ds/Status/prop/color", state_colors[state])

    def update(self):
        self._update_temperature()
        self._update_widget_state()
```

- 2.4 **blynk_paho.py**
主程式

```
#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2024 Volodymyr Shymanskyy for Blynk Technologies Inc.
# SPDX-License-Identifier: Apache-2.0
#
# The software is provided "as is", without any warranties or guarantees (explicit or implied).
# This includes no assurances about being fit for any specific purpose.

import time
import ssl
import config, demo

from paho.mqtt.client import Client, CallbackAPIVersion
from urllib.parse import urlparse

mqtt = Client(CallbackAPIVersion.VERSION2)
device = demo.Device(mqtt)

def on_connect(mqtt, obj, flags, reason_code, properties):
    if reason_code == 0:
        print("Connected [secure]")
        mqtt.subscribe("downlink/#", qos=0)
        device.connected()
    elif reason_code == "Bad user name or password":
        print("Invalid BLYNK_AUTH_TOKEN")
        mqtt.disconnect()
    else:
        raise Exception(f"MQTT connection error: {reason_code}")

def on_message(mqtt, obj, msg):
    payload = msg.payload.decode("utf-8")
    topic = msg.topic
    if topic == "downlink/redirect":
        url = urlparse(payload)
        print("Redirecting...")
        mqtt.connect_async(url.hostname, url.port, 45)
    elif topic == "downlink/reboot":
        print("Reboot command received!")
    elif topic == "downlink/ping":
        pass  # MQTT client library automagically sends the QOS1 response
    elif topic == "downlink/diag":
        print("Server says:", payload)
    else:
        print(f"Got {topic}, value: {payload}")
        device.process_message(topic, payload)

def main():
    mqtt.tls_set(tls_version=ssl.PROTOCOL_TLSv1_2)
    mqtt.on_connect = on_connect
    mqtt.on_message = on_message
    mqtt.username_pw_set("device", config.BLYNK_AUTH_TOKEN)
    mqtt.connect_async(config.BLYNK_MQTT_BROKER, 8883, 45)
    mqtt.loop_start()

    while True:
        device.update()
        time.sleep(1)

if __name__ == "__main__":
    main()
```

### 3. 執行主程式

```
python3 blynk_paho.py
```



### [Device MQTT API 說明書](https://docs.blynk.io/en/blynk.cloud-mqtt-api/device-mqtt-api)