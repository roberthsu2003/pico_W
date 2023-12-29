## 連線ifttt

### 範例1
- 使用get
- 無法使用post,會出錯,server 回應400
- 只傳送一次


```

import time
import network
import urequests as requests

ssid = 'Robert_iPhone'
password = '0926656000'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

#等待連線或失敗
#status=0,1,2正在連線
#status=3連線成功
#<1,>=3失敗的連線

max_wait = 10
send = True

while max_wait > 0:
    status = wlan.status()
    if status < 0 or status >= 3:
        break
    max_wait -= 1
    print("等待連線")
    time.sleep(1)

#處理錯誤
if wlan.status() != 3:
    raise RuntimeError('連線失敗')
else:
    print('連線成功')
    status = wlan.ifconfig()
    print(f'ip={status[0]}')

# urequests官方網址
# https://makeblock-micropython-api.readthedocs.io/en/latest/public_library/Third-party-libraries/urequests.html

while True:
    #取得sensor的資料  
    url = 'https://maker.ifttt.com/trigger/receive_notify/with/key/自已的key?value1=90&value2=100&value3=110'
    
    #使用try/except傳送資料
    
    if(send):
        send = False
        print("送出資料")
        try:
            response = requests.request('GET',url)
        except:
            print(f"無法連線({wlan.status()})")
            if wlan.status() < 0 or wlan.status() > 3:
                print("嘗試重新連線")
                wlan.disconnect()
                wlan.connect(ssid, password)
                if wlan.status() == 3:
                    print("連線成功")
                else:
                    print("連線失敗")
        else:
            print("server接收") #但要檢查status_code,是否回應成功
            if response.status_code == 200:
                print("成功傳送,status_code==200")
            else:
                print("server回應有問題")
                print(f'status_code:{response.status_code}')
        finally:
            response.close()
            
    
        
        
    time.sleep(10)

 ```  
 
--- 

### 範例2
 
- 使用tools module
- 只傳送一次

### ifttt_module

```
from tools import connect,reconnect
import time
import urequests as requests

send:bool = True

# urequests官方網址
# https://makeblock-micropython-api.readthedocs.io/en/latest/public_library/Third-party-libraries/urequests.html

connect()


while True:
    #取得sensor的資料  
    url = 'https://maker.ifttt.com/trigger/receive_notify/with/key/您的key?value1=90&value2=100&value3=110'
    #使用try/except傳送資料
    
    if(send):
        send = False                
        try:  
            print("送出資料")
            response = requests.request('GET',url)
        except:
            #如果出錯response是不會產生的
            reconnect()
        else:
            print("server接收") #但要檢查status_code,是否回應成功
            if response.status_code == 200:
                print("成功傳送,status_code==200")
            else:
                print("server回應有問題")
                print(f'status_code:{response.status_code}')
            response.close()        
        
    time.sleep(10)
 
```    


### toos.py

```
import network
import urequests as requests
import time

ssid = 'Robert_iPhone'
password = '0926656000'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

def connect()->tuple[int,str]:
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)

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

---

### 範例3送出時間和溫度

- 符合條件,每60秒送給ifttt一次
- 傳出現在時間和溫度

```
from tools import connect,reconnect
import time
import urequests as requests
from machine import ADC,Timer,RTC


# urequests官方網址
# https://makeblock-micropython-api.readthedocs.io/en/latest/public_library/Third-party-libraries/urequests.html

def alert(temperature:float):
    print('要爆炸了!')
    rtc = RTC()
    t = rtc.datetime()
    timeString:str = f"{t[0]}-{t[1]}-{t[2]} | {t[4]}:{t[5]}:{t[6]}"
    value1 = timeString
    value2 = temperature
    url = f'https://maker.ifttt.com/trigger/receive_notify/with/key/您的key?value1={value1}&value2={value2}'
    try:  
            print("送出資料")
            response = requests.request('GET',url)
    except:
        #如果出錯response是不會產生的
        reconnect()
    else:
        print("server接收") #但要檢查status_code,是否回應成功
        if response.status_code == 200:
            print("成功傳送,status_code==200")
        else:
            print("server回應有問題")
            print(f'status_code:{response.status_code}')
        response.close()        
        

def callback1(t:Timer):
    global start
    sensor = ADC(4)    
    vol = sensor.read_u16() * (3.3/65535)
    temperature = 27 - (vol-0.706) / 0.001721
    print(f'溫度:{temperature}')    
    delta = time.ticks_diff(time.ticks_ms(), start)
    print(delta)
    #溫度超過24度,並且發送alert()的時間已經大於60秒
    if temperature >= 25 and delta >= 60 * 1000:        
        alert(temperature)
        start = time.ticks_ms()#重新設定計時的時間

adc = machine.ADC(26)
connect()        
start = time.ticks_ms() - 60 * 1000 #應用程式啟動時,計時時間,先減60秒
time1 = Timer()
time1.init(period=1000,callback=callback1)


```



