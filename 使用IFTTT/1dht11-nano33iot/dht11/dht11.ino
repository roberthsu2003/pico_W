// 使用IFTTTu
// 使用arduino nano 33 iot

/*
  連線iftttt,evenName:over30
  和line連線
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "data.h"
#include "DHT.h"

#define dhtData 11
DHT dht(dhtData, DHT11);
int status = WL_IDLE_STATUS;
char server[] = "maker.ifttt.com";
WiFiSSLClient client;

unsigned long getTime1 = millis();

void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //DHTinit
  dht.begin();

  //連線ifttt
  /*一開始就連線的測試
    if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /trigger/over30/with/key/eDqcZfqY_i_BHCZVXCwb6aq7GLPKpdV4q1ePja35Mjq?value1=30&value2=40 HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Connection: close");
    client.println();
    }
  */
}



void loop()
{
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature();//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("無法從DHT傳感器讀取！");
  }
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("攝氏溫度: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("華氏溫度: ");
  Serial.print(f);
  Serial.print("*F\n");

  delay(2000);
  //如果濕度超過90,發送line訊息
  unsigned long currentTime = millis();
  if (currentTime - getTime1 > 30000 && h > 90) {
    //連線ifttt
    if (client.connect(server, 443)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.println("GET /trigger/" + String(EVENNAME) + "/with/key/" + String(KEY) + "?value1=" + String(t) + "&value2=" + String(f) + " HTTP/1.1");
      client.println("Host: maker.ifttt.com");
      client.println("Connection: close");
      client.println();
      
    }
    getTime1 = currentTime;

  }
}
