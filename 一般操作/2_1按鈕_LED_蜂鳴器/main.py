from machine import Pin
from machine import Timer
import time



def running(pin):
    btn.irq(None,Pin.IRQ_RISING) #解決按鈕彈跳問題和一直按按鈕,工作會被放在Queue內,最後有空時,就作queue內的工作           
    print("IRQ with flags:", pin.irq().flags())
    timer1 = Timer()    
    timer1.init(period=1000,callback=led_blink,mode=Timer.ONE_SHOT)
    
def task(n, delay):
    led = machine.Pin("LED", machine.Pin.OUT)
    for i in range(n):
        led.high()
        time.sleep(delay)
        led.low()
        time.sleep(delay)
    print('done')


def led_blink(timer:Timer):
    for i in range(redI):
       redLed.value(1)
       time.sleep_ms(200)
       redLed.value(0)
       time.sleep_ms(200)
    
    for i in range(yellowI):
        yellowLed.value(1)
        time.sleep_ms(200)
        yellowLed.value(0)
        time.sleep_ms(200)
        
    greenLed.value(1)
    time.sleep(3)
    greenLed.value(0)
    buzzerStatus = False
    btn.irq(running, Pin.IRQ_RISING) #解決按鈕彈跳問題
        

if __name__ == '__main__':
    btn = Pin(16,Pin.IN,Pin.PULL_DOWN) #打開上拉電阻
    redLed = Pin(15,Pin.OUT) #紅燈
    yellowLed = Pin(14,Pin.OUT) #黃燈
    greenLed = Pin(13,Pin.OUT) #綠燈
    buzzer = Pin(12,Pin.OUT) #蜂鳴器
    btn.irq(running, Pin.IRQ_RISING) #啟動IRQ,IRQ一執行會停止主thread的工作和次執行序(所有的工作),直到執行完才會釋放main thread,和次執行序
    redI:int = 5 #計紅燈閃的次數
    yellowI:int = 5 #計黃燈閃的次數
    '''irq一執行時,主程式會停止,等irq工作完後才會繼續,可以由以下程式驗證    
    while True:
        print("執行")
        time.sleep(1)
    '''    
    
    
    
    
    
    
    
