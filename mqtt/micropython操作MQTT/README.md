# micropython操作MQTT￼￼￼￼
## [參考網站](https://core-electronics.com.au/guides/getting-started-with-mqtt-on-raspberry-pi-pico-w-connect-to-the-internet-of-things/#setup)

## 1. thonny安裝umqtt.simple套件

![](./images/pic1.png)

## 2. 發佈主題(topic)

### 2_1. tools.py
- **pico連線internet**

```python
import network
import time
import rp2
from machine import WDT

rp2.country('TW')


ssid = 'xxxxxx'
password = 'xxxxxx'


wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)
wlan.config(pm = 0xa11140)

def connect():  

    #等待連線或失敗
    #status=0,1,2正在連線
    #status=3連線成功
    #<1,>=3失敗的連線
    max_wait = 10    

    while max_wait > 0:
        status = wlan.status()
        if status < 0 or status >= 3:
            break
        max_wait -= 1
        print("等待連線")
        time.sleep(1)

    #處理錯誤
    if wlan.status() != 3:
        print('連線失敗,重新開機')
        raise RuntimeError('連線失敗')
        #wdt = WDT(timeout=2000)
        #wdt.feed()
    else:
        print('連線成功')
        status = wlan.ifconfig()
        print(f'ip={status[0]}') 
        
        
def reconnect():
    if wlan.status() == 3: #還在連線,只是傳送的server無回應
        print(f"無法連線({wlan.status()})")
        return
    else:
        print("嘗試重新連線")
        wlan.disconnect()
        wlan.connect(ssid, password)
        connect()
```

### 2_2 main.py發送topic
- **發送topic**

```python
from tools import connect,reconnect
import utime
from umqtt.simple import MQTTClient
from machine import Timer

   
def callback1(t:Timer):
    global counter    
    mqtt_host = "10.170.1.218"    
    mqtt_publish_topic = "a01/device1"  # The MQTT topic for your Adafruit IO Feed

    # Initialize our MQTTClient and connect to the MQTT server
    mqtt_client_id = "pico1"
    user='pi'
    password='raspberry'
    mqtt_client = MQTTClient(
        client_id=mqtt_client_id,
        server=mqtt_host,
        user=user,
        password=password
        )    
    mqtt_client.connect()
    
    try:       
        
        counter += .8        
        # Publish the data to the topic!
        print(f'Publish {counter:.2f}')
        mqtt_client.publish(mqtt_publish_topic, str(counter))
            
            
            
    except Exception as e:
        print(f'Failed to publish message: {e}')
    finally:
        mqtt_client.disconnect()    
    
    
    
    
connect()
counter = 0
time1 = Timer(period=3000, mode=Timer.PERIODIC, callback=lambda t:callback1(t))
```




