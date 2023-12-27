from machine import Pin,ADC
import time


x = ADC(Pin(26))
y = ADC(Pin(27))
switch = Pin(16, Pin.IN)

while True:    
    xValue= x.read_u16()
    yValue = y.read_u16()
    switchValue = switch.value()
    print(f'xValue={xValue}')
    print(f'yValue={yValue}')
    print(f'switchValue={switchValue}')
    time.sleep(1)


