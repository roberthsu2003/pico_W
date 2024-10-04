from machine import Timer,ADC,Pin,PWM,RTC
import tools
from umqtt.simple import MQTTClientt 

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
    mqtt = Client(CallbackAPIVersion.VERSION2)
    #必需提供一個callback的function,當成功連線至MQTT broker
    mqtt.on_connect = on_connect
    #必需提供一個callback的function,當blocker接收收到訂閱的topic
    mqtt.on_message = on_message
    #設定使用者名稱和密碼,Blynk要求使用者名稱都要用"device"
    mqtt.username_pw_set("pi", 'raspberry')
    #使用非同步連接至MQTT Bloker,此方法連接到MQTT broker, 沒有阻止後續程式的執行
    mqtt.connect_async('127.0.0.1', 1883, 45) #無ssl要連線的port是1883
    
    

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
