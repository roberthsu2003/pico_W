from machine import Pin, PWM
from time import sleep

led = Pin(15)

pwm = PWM(led)

pwm.freq(1000) #告知每多少數值時送出電壓給LED

while True:
    for duty in range(65025):
        pwm.duty_u16(duty)
        sleep(0.0001)
    for duty in range(65025, 0, -1):
        pwm.duty_u16(duty)
        sleep(0.0001)