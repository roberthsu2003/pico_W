# HC-SR04超音波測距模組_光敏電阻

- ### 超音波模組工作原理

	- 採用I/O觸發測距，給至少為10us的高電位信號
	- 模組自動發送 8個 40KHZ的方波，自動檢測是否有信號返回
	- 有信號返回，通過I/O輸出一高電位，高電位持續的時間就是超聲波從發射到返回的時間
	- 測試距離 =（高電位時間 x 聲速（340M / S））/ 2
	- 1公分大約58.1us

![](./images/pic2.png)



- ### 技術規格
	- 電源：DC5V/2mA
	- 輸出電位( 1/ 0)：5V/ 0V
	- 精度：3mm
	- 距離範圍：2 ~ 450cm
	- 有效的角度：<15℃
	- 觸發輸入信號：10uS TTL pulse
	- ECHO輸出信號： Input TTL lever signal and the range in proportion
	- 接線方式：VCC、trig (控制端)、echo (接收端)、GND


### 超音波公式
程式撰寫開始前，有個運用超音波時要瞭解的定理，就是音速在空氣中的傳播速度，運用超音波在空氣中行進的速度，花了多少時間來計算與物體間的距離，因為在攝氏零度之海平面音速約為331.5公尺/秒，每升高 1 攝氏度，音速就增加 0.607 公尺/秒，可以列出一個公式：

- 攝氏20度時的音速約為： 331.5 + 0.607*20 = 343.64 公尺/秒
- 音速公尺/秒 換算成 公分/微秒：343.64 * 100 / 1000000 = 0.034364 公分/微秒
- 超音波發射的距離為來回，因此單程距離 = 時間差的距離 / 2

### 使用函式

- utime.sleep_ms(n)：延遲 n 毫秒，應為正數或 0
- utime.sleep_us(n)：延遲 n 微秒，應為正數或 0
- utime.ticks_us()：使其包含以微秒為單位的時間戳。



### 線路圖

- 注意工作電壓為5v

![](./images/pic1.png)



```micro python
from machine import Pin
import utime


trigger = Pin(16, Pin.OUT)
echo = Pin(17, Pin.IN)

def ultra():         #建立一個函式
   print('執行')
   utime.sleep_us(2)  #暫停兩微秒，確保上一個設定低電位已經完成
   trigger.high()
   utime.sleep_us(10)  #拉高電位後，等待10微秒後，立即設定為低電位
   trigger.low()    
   while echo.value() == 0:         #建立一個while迴圈檢查回波引腳是否值為0，紀錄當時時間
       signaloff = utime.ticks_us()   
   while echo.value() == 1:         #建立一個while迴圈檢查回波引腳是否值為1，紀錄當時時間
       signalon = utime.ticks_us()  
   timepassed = signalon - signaloff    #計算發送與接收時間差
   distance = (timepassed * 0.0343) / 2  #聲波行進時間 x 聲速(343.2 m/s，即每微秒0.0343公分)，來回距離再除以2  
   print("The distance is ： ",distance,"cm")

while True:
   ultra()
   utime.sleep(1)  #等待1秒

```

