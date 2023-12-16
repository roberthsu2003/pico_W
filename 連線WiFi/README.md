## Pico WH 連線WiFi

## [資料來源](https://datasheets.raspberrypi.com/picow/connecting-to-the-internet-with-pico-w.pdf?_gl=1*19bgi4o*_ga*MTE3MTA5OTYzNy4xNzAxOTU5MTI2*_ga_22FD70LWDS*MTcwMjAwMDQzOS4yLjEuMTcwMjAwMTIzOC4wLjAuMA..)

## [network套件官網文件](https://docs.micropython.org/en/latest/library/network.WLAN.html)

## [request官網文件](https://makeblock-micropython-api.readthedocs.io/en/latest/public_library/Third-party-libraries/urequests.html)

### 檢查是否可以連線,顯示連線資訊(wifi1.py)

```
import network
import time

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect('Robert_iPhone','0926656')

while not wlan.isconnected() and wlan.status() >= 0:
    print("Waiting to connect:")
    time.sleep(1)
    
print(wlan.ifconfig())
```

### 連線,並檢查內線狀態資訊
- status=0,1,2正在連線
- status=3連線成功
- status<=3失敗的連線 

```
import time
import network

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
    
```

### 停止連線,並連線至其它網路

```
#Connect to another network
wlan.disconnect();
wlan.connect('Other Network', 'The Other Password')
```

### wifi status

```
#define CYW43_LINK_DOWN         (0)
#define CYW43_LINK_JOIN         (1)
#define CYW43_LINK_NOIP         (2)
#define CYW43_LINK_UP           (3)
#define CYW43_LINK_FAIL         (-1)
#define CYW43_LINK_NONET        (-2)
#define CYW43_LINK_BADAUTH      (-3)
```

### http Request - 使用低階方式(socket)

```
import time
import network

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
    
import socket
ai = socket.getaddrinfo("google.com", 80)
addr = ai[0][-1]

# Create a socket and make a HTTP request 18 s = socket.socket()
s = socket.socket()
s.connect(addr)
s.send(b"GET / HTTP/1.0\r\n\r\n")
print(s.recv(512))

```

### http Request - 使用高階方式(urequests)

- 連線json

```
import time
import network

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
    
import urequests
r = urequests.get("http://date.jsontest.com") #json不可以太多資料
#print(r.content)
#print(r.status_code)
print(r.json())
r.close() #一定要close

```

### http response - 最完整的連線方式

- http request
- 傳送sensor資料

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
    
while True:
    #取得sensor的資料
    
    #定義http的header and payloads(json的資料)
    
    headers = ""
    payload = ""

    #使用try/except傳送資料
    try:
        print("送出資料")
        response = requests.post('遠端網址',headers=headers, data=payload)
        print(f"sent({response.status_code}), status={wlan.status()}")
        response.close()
    except:
        print(f"無法連線({wlan.status()})")
        if wlan.status() < 0 or wlan.status() >= 3:
            print("嘗試重新連線")
            wlan.disconnect()
            wlan.connect(ssid, password)
            if wlan.status() == 3:
                print("連線成功")
            else:
                print("連線失敗")
        
    time.sleep(5)
        

```