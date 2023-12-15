## 重新啟動,倒數計時-WTD(Watchdog timer)
- minimum 1S
- maximum 8388 ms

```
From machine import WDT
```

### 線路圖

![](./images/pic1.png)

### 重新啟動

```
from machine import WDT

#取得目前日期

wdt = WDT(timeout=2000)
wdt.feed()
```


