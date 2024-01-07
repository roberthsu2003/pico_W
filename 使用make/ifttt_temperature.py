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
    url = f'https://maker.ifttt.com/trigger/receive_notify/with/key/eDqcZfqY_i_BHCZVXCwb6aq7GLPKpdV4q1ePja35Mjq?value1={value1}&value2={value2}'
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
