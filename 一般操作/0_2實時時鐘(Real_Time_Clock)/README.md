## Pico 有自帶實時時鐘


```
from machine import RTC
```

### 線路圖

![](./images/pic1.png)

### 取得目前日期

```
from machine import RTC

#取得目前日期
rtc = RTC()
print(rtc.datetime())

-------------------
(2023, 12, 15, 4, 13, 32, 19, 0)
2023年12月15日星期五,13點,32分,19秒
```

### 自訂日期
#### 為何要自訂即時時間?
- RTC的時間是取得電腦的時間(當電腦連線時是正常的現在日期和時間)
- 當單獨運作時(無連接電腦,所以要透過RTC sensor,或wifi取得目前的時間)

```
from machine import RTC
rtc = RTC()
rtc.datetime((2017,8,23,2,12,48,0,0))
print(rtc.datetime())

-------------
(2017, 8, 23, 2, 12, 48, 1, 0)
```

