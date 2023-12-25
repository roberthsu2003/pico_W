## 執行緒使用
- 只有2Core
- 所以1次只可以建立一個thread

### 線路圖

![](./images/pic1.png)

```
import time, _thread, machine

def task(n, delay):
    led = machine.Pin("LED", machine.Pin.OUT)
    for i in range(n):
        led.high()
        time.sleep(delay)
        led.low()
        time.sleep(delay)
    print('done')

_thread.start_new_thread(task, (10, 0.5))

while True:    
    print("true")
    time.sleep(1)
```


