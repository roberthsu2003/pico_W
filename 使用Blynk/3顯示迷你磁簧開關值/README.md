# 迷你磁簧開關和Blynk
- ### 學習讓Arduino_迷你磁簧開關和Blynk手機App連線,使用widgetLED,傳送虛擬pin腳的訊號出去，由device 傳送給 App 訊號
### 線路圖
![](reedSwitch_bb.jpg)

### 實體線路圖
![](IMG_0435.jpg)

### Blynk App內設定專案
### App內,板子的設定必需設定為Arduino nano(因為腳位和Arduino nano 33 iot相同)
### 使用DISPlAY內的Led
### [Blynk widget 說明頁](https://docs.blynk.io/en/blynk.apps/widgets)
![](IMG_1BF.jpeg)

### Blynk App專案畫面 
![](IMG_CD55.jpeg)

### Blynk_可變電阻影片
[![](https://img.youtube.com/vi/JEFEs4sPM48/2.jpg)](https://youtu.be/JEFEs4sPM48)



```C++
/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your````
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino MKR 1010
  to connect your project to Blynk.

  Note: This requires WiFiNINA library
    from http://librarymanager/all#WiFiNINA

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include "data.h"
//定義實體ledPin腳
#define ledPin 13

//定義接收磁開關的pin腳
#define sensor_d12 12
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = AUTH;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = SSID;
char pass[] = PASS;

//必需使用BlynkTimer來建立間隔一段時間，執行function,不可以使用delay
BlynkTimer timer;

//由於使用WidgetLED，必需建立WidgetLED實體led0,建構式內的參數代表的是虛擬pinV0,如果使用led0.on(),代表由device送出on給Server V0,Server V0再傳送給手機app
WidgetLED led0(V0);
void setup()
{
  // Debug console
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);
  pinMode(sensor_d12, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  
}

void myTimerEvent(){  
  int sensorValue = digitalRead(sensor_d12);
  //必需調整,沒有磁鐵時,輸出為1
  Serial.println(sensorValue);
  if(sensorValue==0){
     led0.on();
     digitalWrite(ledPin,HIGH);
  }else{
    led0.off();
    digitalWrite(ledPin,LOW);
  }
}
```

