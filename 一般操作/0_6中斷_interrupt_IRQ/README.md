## 中斷_interrupt_IRQ

- Pin.IRQ_FALLING(1->0)
- Pin.IRQ_RISING,(0->1)

### 線路圖

![](./images/pic1.png)

```
from machine import Pin

p2 = Pin(2, Pin.IN, Pin.PULL_UP)
p2.irq(lambda pin: print("IRQ with flags:", pin.irq().flags()), Pin.IRQ_FALLING)

```


