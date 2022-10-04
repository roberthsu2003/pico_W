# 使用IFTTT讓esp32發送溫溼度訊息給line群組
## 讓Arduino的DHT11發送訊息給WebHook,再由WebHook轉送給Line群組 

```c++
// 使用IFTTT
// 使用esp32

/*
  連線iftttt,evenName:nighting
  和line連線
*/


#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "data.h"

int status = WL_IDLE_STATUS;
WiFiMulti WiFiMulti;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

 
  
  
}



void loop()
{
  //連線ifttt
 WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    //client -> setCACert(rootCACertificate);
    client -> setInsecure(); //不要檢查憑證的驗證

    {
      //建立程式區塊,確認所有https這個區塊結束後,https變數記憶體被釋放，完成後才可以delete client 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, "https://maker.ifttt.com/trigger/" + String(EVENNAME) + "/with/key/" + String(KEY) + "?value1=30&value2=40&value3=50")) {  // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }

      // End extra scoping block
    }
  
    delete client;
  } else {
    Serial.println("Unable to create client");
  }

  Serial.println();
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
}

```