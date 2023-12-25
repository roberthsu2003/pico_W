# 可變電阻控制LED(ADC-PWM)

## 線路圖

![](./images/pic1.png)

```
from machine import Pin, PWM, ADC

pwm = PWM(Pin(15))
adc = ADC(Pin(26))

pwm.freq(1000)

while True:
	duty = adc.read_u16()
	pwm.duty_u16(duty)


```

