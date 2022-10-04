# 可變電阻和Blynk.Console
## 學習讓Arduino_可變電阻和手機，網頁整合
### 線路圖
![](resistance_bb.jpg)

### 實體線路圖
![](IMG_0429.jpg)

### Blynk.Console
#### Template info設定

![](pic1.png)

#### Template Datastreams 設定

![](pic2.png)

#### Template Web Dashboard 設定

![](pic3.png)

#### Device 設定
1. 刪除原來的
2. 建立新的Device

![](pic4.png)

### Blynk App內設定專案

1.會依據Blynk內的Device,建立Device

![](pic5.png)

2.在Device內建立UI畫面

![](pic6.png)



### Blynk_可變電阻影片
[![](https://img.youtube.com/vi/fGtkoiCtA9Q/1.jpg)](https://youtu.be/fGtkoiCtA9Q)


```C++
#define BLYNK_PRINT Serial
#include "data.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = ID;
char pass[] = PASS;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
  Blynk.run();
}
```

