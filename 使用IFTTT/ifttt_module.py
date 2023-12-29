import tools
import time

send:bool = True

# urequests官方網址
# https://makeblock-micropython-api.readthedocs.io/en/latest/public_library/Third-party-libraries/urequests.html

while True:
    #取得sensor的資料  
    url = 'https://maker.ifttt.com/trigger/receive_notify/with/key/eDqcZfqY_i_BHCZVXCwb6aq7GLPKpdV4q1ePja35Mjq?value1=90&value2=100&value3=110'
    #使用try/except傳送資料
    
    if(send):
        send = False
        print("送出資料")
        try:
            response = requests.request('GET',url)
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
 
 
 



