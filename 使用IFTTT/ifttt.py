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



while True:
    #取得sensor的資料
    
    #定義http的header and payloads(json的資料)
    data = {"value1":"50","value2":"100","value3":"90"}    
    url = 'https://maker.ifttt.com/trigger/receive_notify/with/key/eDqcZfqY_i_BHCZVXCwb6aq7GLPKpdV4q1ePja35Mjq?value1=90&value2=100&value3=110'
    
    #使用try/except傳送資料
    try:
        if(send):
            send = False
            print("送出資料")
            try:
                response = requests.request('GET',url)
            except:
                print("傳送失敗")
            else:
                print("送出成功")
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
        
        time.sleep(10)
        
