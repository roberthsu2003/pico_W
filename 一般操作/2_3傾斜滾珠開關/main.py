from machine import Pin
from machine import Timer


led = Pin(15,Pin.OUT)
tilt_switch = Pin(16, Pin.IN, Pin.PULL_UP) # 上接電阻

def check_tilt(t:Timer):
    tilt_value = tilt_switch.value()
    print(tilt_value)
    led.value(tilt_value)
    

time1 = Timer() 
time1.init(period=1000, mode=Timer.PERIODIC, callback=check_tilt)


