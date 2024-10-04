# 本地區網Bloker
**光敏電阻_led_可變電阻_溫度**


## 1. 專案架構

![](./images/pic2.png)


## 2. 線路圖

![](./images/pic1.png)

## 3. 程式碼

### 3.1 第1階段-硬體測試連結階段
- **main.py**

```micropython
from machine import Timer,ADC,Pin,PWM,RTC
def do_thing(t):
    '''
    處理溫度和光線
    '''
    reading = adc.read_u16() * conversion_factor
    temperature = 27 - (reading - 0.706)/0.001721
    print(f'溫度:{temperature}')
    light_value = adc_light.read_u16()
    print(f'光線:{light_value}')
    
    
def do_thing1(t):
    '''
    處理可變電阻
    '''
    adc1 = ADC(Pin(26))
    duty = adc1.read_u16()
    pwm.duty_u16(duty)    
    print(f'可變電阻:{round(duty/65535*10)}')
    
def main():
    t1 = Timer(period=1000, mode=Timer.PERIODIC, callback=do_thing)
    t2 = Timer(period=500, mode=Timer.PERIODIC, callback=do_thing1)
    
if __name__ == "__main__":
    #pico_連結電腦時的寫法,要用connect
    try:
        tools.connect()
    except RuntimeError as e:
        print(f"{{e}")
    else:
        #sensor setup
        adc = ADC(4) #內建溫度感測器
        adc_light = ADC(Pin(28)) #光線感測器
        pwm = PWM(Pin(15),freq=50) #可變電阻
        conversion_factor = 3.3 / (65535) #電壓轉換率    
        main()
```

### 3.2 第2階段-硬體測試成功並增加網路功能

### **tools.py**

```micropython
import network
import urequests as requests
import time
import rp2
from machine import WDT

rp2.country('TW') #設定我們的wifi的地區是台灣(可以不設)
'''
ssid = 'A590301'
password = 'A590301AA'
'''
ssid = 'robertHome'
password = '0926656000'

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
        raise RuntimeError('連線失敗') #開發階段,出現錯誤,中斷執行
        #wdt = WDT(timeout=2000) #無連接電腦時,重新開機(成品時,請使用這個)
        #wdt.feed()
    else:
        print('連線成功')
        status = wlan.ifconfig()
        print(f'ip={status[0]}') 
        
        
def reconnect():
    if wlan.status() == 3: #還在連線,只是傳送的server無回應
        print(f"執行reconnect,連線正常({wlan.status()})")
        return
    else:
        print("嘗試重新連線")
        wlan.disconnect()
        wlan.connect(ssid, password)
        connect() #再連線一次
```


**main.py**

```micropython
from machine import Timer,ADC,Pin,PWM,RTC
import tools

def do_thing(t):
    '''
    處理溫度和光線
    '''
    reading = adc.read_u16() * conversion_factor
    temperature = 27 - (reading - 0.706)/0.001721
    print(f'溫度:{temperature}')
    light_value = adc_light.read_u16()
    print(f'光線:{light_value}')
    
    
def do_thing1(t):
    '''
    處理可變電阻
    '''
    adc1 = ADC(Pin(26))
    duty = adc1.read_u16()
    pwm.duty_u16(duty)    
    print(f'可變電阻:{round(duty/65535*10)}')


def main():
    t1 = Timer(period=1000, mode=Timer.PERIODIC, callback=do_thing)
    t2 = Timer(period=500, mode=Timer.PERIODIC, callback=do_thing1)

if __name__ == "__main__":
    #pico_連結電腦時的寫法,要用connect
    try:
        tools.connect()
    except RuntimeError as e:
        print(f"{{e}")
    else:
        #sensor setup
        adc = ADC(4) #內建溫度感測器
        adc_light = ADC(Pin(28)) #光線感測器
        pwm = PWM(Pin(15),freq=50) #可變電阻
        conversion_factor = 3.3 / (65535) #電壓轉換率    
        main()
```

### 3.3 第3階段-硬體,網路,MQTT











