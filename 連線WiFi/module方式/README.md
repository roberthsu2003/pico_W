## 使用module的方式連結

### main.py

```
from tools import connect,reconnect
import urequests as requests
import utime
   
def callback1(t:Timer):
        
    url = 'xxxxx'    
    
    try:
	     #如果server 沒有回應,不會有response     
        response = requests.get(url)        
    except:
        reconnect()
    else:
        print("server接收") #有response,可能是不正確的.所以要檢查status_code,是否回應成功        
        if response.status_code == 200:
            print("成功傳送,status_code==200")
        else:
            print("server回應有問題")
            print(f'status_code:{response.status_code}')
        response.close() #有response就要關閉
    
    
connect()
time1 = Timer()
time1.init(period=10000,callback=callback1)
```


### tools.py(連線internet)
- 更改ssid,password

```
import network
import urequests as requests
import time
import rp2
from machine import WDT

rp2.country('TW') #設定我們的wifi的地區是台灣(可以不設)

ssid = 'xxxx'
password = 'xxxxx'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)
wlan.config(pm = 0xa11140) #預設是省電模式,可以設為非省電模式

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
        #raise RuntimeError('連線失敗') #開發階段,出現錯誤,中斷執行
        wdt = WDT(timeout=2000) #無連接電腦時,重新開機(成品時,請使用這個)
        wdt.feed()
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
        connect() #再連線一次
```