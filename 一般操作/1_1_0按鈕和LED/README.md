# 按鈕_LED

## 上拉電阻(Pin.PULL_UP)
- ### 按鈕使用上拉電阻,代表GPIO14,內有電阻,並且發出3.3V電壓,另一端接地
![](./images/button02.png)

## 下拉電阻(Pin.PULL_Down)
- ### 按鈕使用下拉電阻,代表GPIO14,內有電阻,並且接地.另一端接電壓

### 線路圖
![下拉電阻線路圖](./images/pic1.png)

```
from machine import Pin
import time

led = Pin(15, Pin.OUT)
button = Pin(14, Pin.IN, Pin.PULL_DOWN)

while True:
    if button.value():
	    led.toggle()
        time.sleep(0.5)
```



