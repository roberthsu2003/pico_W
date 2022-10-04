// 使用IFTTT
// 使用arduino nano 33 iot

/*
  連線iftttt,evenName:over30
  和line連線
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "data.h"
#define LIGHTS 36

int status = WL_IDLE_STATUS;
WiFiMulti WiFiMulti;
unsigned long commitTime = 1000 * 10;
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
  int lightValue = analogRead(LIGHTS);
  byte percentValue = map(lightValue,70,3700,0,100);
  Serial.println(percentValue);
  unsigned long currentTime = millis();
  if(percentValue >= 70 && currentTime-commitTime > 1000*10){
    Serial.println("光線太暗:" + String(percentValue)); 
    ifttt(percentValue,100,100); 
    commitTime=millis();
  }
  delay(100);
}

void ifttt(int value1,int value2,int value3){
  //連線ifttt
 WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    //client -> setCACert(rootCACertificate);
    client -> setInsecure(); //不要檢查憑證的驗證

    {
      //建立程式區塊,確認所有https這個區塊結束後,https變數記憶體被釋放，完成後才可以delete client 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, "https://maker.ifttt.com/trigger/" + String(EVENNAME) + "/with/key/" + String(KEY) + "?value1=" + String(value1)+ "&value2=" + String(value2) + "&value3=" +String(value3))) {  // HTTPS
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

  
}
