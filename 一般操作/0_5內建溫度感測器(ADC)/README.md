## 內建溫度感測器(ADC)
- ADC為12-bit(0~4095)
- RP2024提供5個ADC(channel 0~4)
- GP26,GP27,GP28->一般使用
- GP29->可以測量目主機版電壓(VSYS)
- 最後一個為溫度感測器專用

### 線路圖

![](./images/pic1.png)

```
From machine import ADC
```


### 使用GPIO連線 
- GP26

```
adc = machine.ADC(26) # Connect to GP26, which is channel 0
```


### 使用channel連線



```
adc = machine.ADC(4) # Connect to the internal temperature sensor adc = machine.ADC(0) # Connect to channel 0 (GP26)
```


### 溫度範例

```
import machine
import utime

sensor_temp = machine.ADC(4)
conversion_factor = 3.3 / (65535)

while True:
    reading = sensor_temp.read_u16() * conversion_factor
    
    # The temperature sensor measures the Vbe voltage of a biased bipolar diode, connected to the fifth ADC channel
    # Typically, Vbe = 0.706V at 27 degrees C, with a slope of -1.721mV (0.001721) per degree. 
    temperature = 27 - (reading - 0.706)/0.001721
    print(temperature)
    utime.sleep(2)

```


### 溫度,每隔60秒,發送一次alert()

```
from machine import ADC,Timer
import time
# Typically, Vbe = 0.706V at 27 degrees C, with a slope of -1.721mV (0.001721) per degree.

def alert():
    print('要爆炸了!')
    
def callback1(t:Timer):
    global start
    sensor = ADC(4)    
    vol = sensor.read_u16() * (3.3/65535)
    temperature = 27 - (vol-0.706) / 0.001721
    print(f'溫度:{temperature}')    
    delta = time.ticks_diff(time.ticks_ms(), start)
    print(delta)
    #溫度超過24度,並且發送alert()的時間已經大於60秒
    if temperature >= 24 and delta >= 60 * 1000:        
        alert()
        start = time.ticks_ms()#重新設定計時的時間
        

start = time.ticks_ms() - 60 * 1000 #應用程式啟動時,計時時間,先減60秒
    
time1 = Timer()
time1.init(period=1000,callback=callback1)

```