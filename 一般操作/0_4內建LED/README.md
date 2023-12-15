## 內建LED
- 使用字串"LED"
- 使用字串"WL_GPIO0"


```
From machine import Pin
```

### 線路圖

![](./images/pic1.png)

### 使用REPL操控

```
>>> from machine import Pin
>>> led = Pin("LED", Pin.OUT)
>>> led.value(1)
>>> led.value(0)

```

### blink

```
from machine import Pin, Timer

led = Pin("LED", Pin.OUT)
tim = Timer()
def tick(timer):
    global led
    led.toggle()

tim.init(freq=2.5, mode=Timer.PERIODIC, callback=tick)

```


