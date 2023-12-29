# HC-SR04超音波測距模組_光敏電阻

## 影片展示
[![](https://img.youtube.com/vi/HT5KaSnDzY4/2.jpg)](https://youtu.be/HT5KaSnDzY4)


- ### 超音波模組工作原理

	- 採用I/O觸發測距，給至少為10us的高電位信號
	- 模組自動發送 8個 40KHZ的方波，自動檢測是否有信號返回
	- 有信號返回，通過I/O輸出一高電位，高電位持續的時間就是超聲波從發射到返回的時間
	- 測試距離 =（高電位時間 x 聲速（340M / S））/ 2
	- 1公分大約58.1us

![](./images/pic2.png)



- ### 技術規格
	- 電源：DC5V/2mA
	- 輸出電位( 1/ 0)：5V/ 0V
	- 精度：3mm
	- 距離範圍：2 ~ 450cm
	- 有效的角度：<15℃
	- 觸發輸入信號：10uS TTL pulse
	- ECHO輸出信號： Input TTL lever signal and the range in proportion
	- 接線方式：VCC、trig (控制端)、echo (接收端)、GND


### 超音波公式
程式撰寫開始前，有個運用超音波時要瞭解的定理，就是音速在空氣中的傳播速度，運用超音波在空氣中行進的速度，花了多少時間來計算與物體間的距離，因為在攝氏零度之海平面音速約為331.5公尺/秒，每升高 1 攝氏度，音速就增加 0.607 公尺/秒，可以列出一個公式：

- 攝氏20度時的音速約為： 331.5 + 0.607*20 = 343.64 公尺/秒
- 音速公尺/秒 換算成 公分/微秒：343.64 * 100 / 1000000 = 0.034364 公分/微秒
- 超音波發射的距離為來回，因此單程距離 = 時間差的距離 / 2

### 使用函式

- utime.sleep_ms(n)：延遲 n 毫秒，應為正數或 0
- utime.sleep_us(n)：延遲 n 微秒，應為正數或 0
- utime.ticks_us()：使其包含以微秒為單位的時間戳。

## Blynk建立流程

#### 1. 建立Template
- V0 -> distance
- V1 -> light
- 
#### 2. 建立Device
- 因為使用的是RESTful的連線,最重要是是token的密碼

#### 3.使用VSCode thunder client 測試

#### 4. 程式

- [RESTful的說明](https://docs.blynk.io/en/blynk.cloud/device-https-api)

- 此程式一次改變2個值,使用此 Blynk的API(Update Multiple Datastreams Simultaneously)

### 線路圖

- 注意工作電壓為5v

![](./images/pic1.png)


### 程式碼

Main.py

```micro python
BLYNK_AUTH_TOKEN = "自已的Code"

from tools import connect,reconnect
import urequests as requests
from machine import Pin,ADC,Timer
import utime

adc_light = ADC(Pin(28))
trigger = Pin(16, Pin.OUT)
echo = Pin(17, Pin.IN)
connect()

def ultra()->float:      #建立一個函式
   utime.sleep_us(2)  #暫停兩微秒，確保上一個設定低電位已經完成
   trigger.high()
   utime.sleep_us(10)  #拉高電位後，等待10微秒後，立即設定為低電位
   trigger.low()    
   while echo.value() == 0:         #建立一個while迴圈檢查回波引腳是否值為0，紀錄當時時間
       signaloff = utime.ticks_us()   
   while echo.value() == 1:         #建立一個while迴圈檢查回波引腳是否值為1，紀錄當時時間
       signalon = utime.ticks_us()  
   timepassed = signalon - signaloff    #計算發送與接收時間差
   distance = (timepassed * 0.0343) / 2  #聲波行進時間 x 聲速(343.2 m/s，即每微秒0.0343公分)，來回距離再除以2  
   return distance
   
def lightSensor()->float:
    light_value = adc_light.read_u16()
    return light_value


   
def callback1(t:Timer):
    distance = ultra()
    light_value = lightSensor()
    
    #不要使用https呼叫,沒有傳出值
    #更新V0->distance
    #更新V1->light
    print(distance)
    print(light_value)
    
    url = f'https://blynk.cloud/external/api/batch/update?token={BLYNK_AUTH_TOKEN}&v0={distance}&v1={light_value}'
    try:        
        response = requests.get(url)
        print("text")
        print("送出資料")
    except:
        reconnect()
    else:
        print("server接收") #但要檢查status_code,是否回應成功        
        if response.status_code == 200:
            print("成功傳送,status_code==200")
        else:
            print("server回應有問題")
            print(f'status_code:{response.status_code}')
           
        
        response.close()
        
time1 = Timer()
time1.init(period=5000,callback=callback1)

```

tools.py

```python
import network
import urequests as requests
import time

#ssid = 'Robert_iPhone'
#password = '0926656000'

ssid = 'robertHome'
password = '0926656000'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

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
        print('連線失敗')
        raise RuntimeError('連線失敗')
    else:
        print('連線成功')
        status = wlan.ifconfig()
        print(f'ip={status[0]}') 
        
        
def reconnect():
    while True:
        print(f"無法連線({wlan.status()})")
        if wlan.status() < 0 or wlan.status() >= 3:
            print("嘗試重新連線")
            wlan.disconnect()
            wlan.connect(ssid, password)
            if wlan.status() == 3:
                print("連線成功")
                break
            else:
                print("連線失敗")
        time.sleep(1)

```


