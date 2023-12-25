# Raspberry Pico_W
## 硬體設備
### 主要設備:
Raspberry pico_W
![Raspberry pico_W1](./images/pick_w1.jpeg)
![Raspberry pico_W2](./images/pick_w2.jpeg)
![Raspberry pico_W3](./images/pick_w3.jpeg)

### VSYS
- min 1.8V,外部電源輸入
- max 5.5V,外部電源輸入

### VBUS 5V(+10%,-10%)來自於USB的電壓

### 工作電壓 3.3V

### 輸出電壓 3.3V


### [官方說明文件 pico W](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html#raspberry-pi-pico-w19)

### [官方Getting Start](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html)

### [microPython for Rp2](https://docs.micropython.org/en/latest/rp2/general.html)

### [pico Examples](https://github.com/raspberrypi/pico-micropython-examples/tree/master)

### [picozeor官網](https://picozero.readthedocs.io/en/latest/)

### 購買網址
[pico主板](https://piepie.com.tw/product/raspberry-pi-pico-wh?hilite=pico)

[工具套件](https://piepie.com.tw/product/gpio-game-console-starter-kit)
 
### [周邊零件](./周邊零件/README.md)

## 一般操作
### 內建硬體

0_1. [計時器](./一般操作/0_1計時器/)

0_2. [實時時鐘(RTC)](./一般操作/0_2實時時鐘(Real_Time_Clock))

0_3. [重新啟動](./一般操作/0_3重新啟動(WTD))

0_4. [內建LED](./一般操作/0_4內建LED)

0_5. [內建溫度感測器(ADC)](./一般操作/0_5內建溫度感測器(ADC))

0_6. [中斷_interrupt_IRQ](./一般操作/0_6中斷_interrupt_IRQ)

0_7. [執行緒使用](./一般操作/0_7執行緒使用)

0_8. [連線WiFi](./連線WiFi)

### 外接硬體

1_0. [按鈕-下接電阻](./一般操作/1_1_0按鈕和LED/)

1_1. [按鈕-LED-蜂鳴器](./一般操作/1_1_1按鈕_LED_蜂鳴器) 

1_2. [PWM控制LED](./一般操作/1_1_2_PWM控制LED)


## Blynk網路服務
### [Blynk說明](./使用Blynk)
1. [控制LED](./使用Blynk/1控制LED/)

2. [顯示可變電阻值](./使用Blynk/2顯示可變電阻值/)

3. [顯示迷你磁簧開關值](./使用Blynk/3顯示迷你磁簧開關值/)
	- 使用virtual pin 傳送資料 -> WidgetLed class

4. [顯示按鈕狀態](./使用Blynk/4顯示按鈕狀態/)
	- 使用virtual pin 傳送資料 -> Blynk.virtualWrite(V4, HIGH)

5. [控制RGBLED](./使用Blynk/5控制RGBLED/)

## Blynk.Console 服務
### [Blynk.Console 說明](./使用Blynk_Console/)
1. [控制LED](./使用Blynk_Console/1控制LED/)

2. [顯示可變電阻值](./使用Blynk_Console/2顯示可變電阻值/)

3. [控制RGBLED](./使用Blynk_Console/3控制RGBLED/)

4. [按鈕_7段顯示器_74hc595](./使用Blynk_Console/4按鈕_7段顯示器_74hc595)

5. [nano33-io版 濕度_發出警告](./使用Blynk_Console/5溫濕度_發出警告/)
	- 圖表顯示，當超過指定溫度或溼度發出通知

5. [esp32版 溫濕度_發出警告](./使用Blynk_Console/5溫濕度_發出警告_esp32s)
	- 圖表顯示，當超過指定溫度或溼度發出通知


## 及時資料庫
1. [網頁顯示LED狀態](https://github.com/roberthsu2003/smartHome/tree/master/%E5%8F%8A%E6%99%82%E8%B3%87%E6%96%99%E5%BA%AB/1led_control)

2. [網頁監控觸控裝置](https://github.com/roberthsu2003/smartHome/tree/master/%E5%8F%8A%E6%99%82%E8%B3%87%E6%96%99%E5%BA%AB/2touch_sensor)

3. [網頁監控環境溫溼度](https://github.com/roberthsu2003/smartHome/tree/master/%E5%8F%8A%E6%99%82%E8%B3%87%E6%96%99%E5%BA%AB/3dht11) 

## LihgtBlue手機藍牙app
1. [手機藍牙控制LED](https://github.com/roberthsu2003/smartHome/tree/master/%E4%BD%BF%E7%94%A8%E8%97%8D%E7%89%99/1led_control)

## IFTTT服務
1. [使用GET傳送資料](./使用IFTTT/)



## ThingSpeak 服務
1. [收集資料，繪制圖表](https://github.com/roberthsu2003/smartHome/tree/master/%E4%BD%BF%E7%94%A8ThingSpeak)


## [將Raspberry Pico W當作Web Server](./當作WebServer/)(建立控制網頁)


