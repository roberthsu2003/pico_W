// 使用LED,Touch,DHT11和Firebase整合
// 使用arduino nano 33 iot

#include <SPI.h>
#include <WiFiNINA.h>
#include "Firebase_Arduino_WiFiNINA.h"
#include "data.h"
#include "DHT.h"
#include <Thread.h>
#include <ThreadController.h>

#define dhtData 11
#define led 13
#define touchSensor 12

//建立時間管理
ThreadController controll = ThreadController();
Thread DHTThread = Thread();
Thread LEDThread = Thread();
Thread TouchThread = Thread();


//DHT初始化
DHT dht(dhtData, DHT11);

//Firebase初始化
FirebaseData firebaseData;



unsigned long getTime1 = millis();
float h;
float f;
float t;
bool currentState;

void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println();
  //啟動時間管理
  DHTThread.onRun(DHTcallBack);
  DHTThread.setInterval(2000);
  controll.add(&DHTThread);
  
  LEDThread.onRun(LEDcallBack);
  LEDThread.setInterval(500);
  controll.add(&LEDThread);

  TouchThread.onRun(TouchcallBack);
  TouchThread.setInterval(100);
  controll.add(&TouchThread);
  
  //連線wifi
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

  //LEDinit
  pinMode(led,OUTPUT);

  //Touch
  pinMode(touchSensor, INPUT);
  //得第一次的currentState
  currentState = digitalRead(touchSensor);
  
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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}



void loop()
{
  controll.run(); 
  
}

void DHTcallBack(){
  h = dht.readHumidity();//讀取濕度
  t = dht.readTemperature();//讀取攝氏溫度
  f = dht.readTemperature(true);//讀取華氏溫度
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
  String humidityPath = "DHT11/humidity";
  String temperaturePath = "DHT11/temperature";

  if(Firebase.setFloat(firebaseData,humidityPath,h)){
    if(firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
  }else{
    Serial.println("Firebase DHT錯誤:");
    Serial.println(firebaseData.errorReason());
  }

  if(Firebase.setFloat(firebaseData,temperaturePath,t)){
    if(firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
  }else{
    Serial.println("Firebase DHT錯誤:");
    Serial.println(firebaseData.errorReason());
  }

  Serial.println("loop");
  //如果濕度超過30,發送line訊息
 //同時連線firebase 和 ifttt會出錯
  
  unsigned long currentTime = millis();
  Serial.println("currentTime:"+String(currentTime));
  Serial.println("getTime1:"+String(getTime1));
  Serial.println("intervalTime:"+String(currentTime-getTime1));
  if ((currentTime - getTime1 > 30000) && h > 90 && t > 28) {
    //連線ifttt
    Serial.println("準備連線IFTTT");
    //ssl連線初始化
    
    WiFiSSLClient client = firebaseData.getWiFiClient(); //說明https://github.com/mobizt/Firebase-Arduino-WiFiNINA
    int status = WL_IDLE_STATUS;
    char server[] = "maker.ifttt.com";
    
    if (client.connect(server, 443)) {
      Serial.println("connected to IFTTT");
      // Make a HTTP request:
      client.println("GET /trigger/" + String(EVENNAME) + "/with/key/" + String(KEY) + "?value1=" + String(t) + "&value2=" + String(f) + " HTTP/1.1");
      client.println("Host: maker.ifttt.com");
      client.println("Connection: close");
      client.println();      
    }
    
    getTime1 = currentTime;
  }
  
}

void LEDcallBack(){
  String path = "ledControl/state";
  if(Firebase.getBool(firebaseData,path)){
     Serial.println("getNode");
     Serial.println(firebaseData.boolData());
     if(firebaseData.boolData()){
      digitalWrite(led,HIGH);
     }else{
      digitalWrite(led,LOW);
     }
  }else{
    Serial.println("Firebase LED錯誤:");
     Serial.println(firebaseData.errorReason());
  }    
}

void TouchcallBack(){
   bool state = digitalRead(touchSensor);
  String path = "touchSensor/touch";
  
  if(state != currentState){
    currentState = state;
    Serial.println("touch狀態" + String(state));
    Serial.println("上傳");
    if(Firebase.setBool(firebaseData, path, state)){
      
      if(firebaseData.dataType() == "boolean"){
        Serial.print("及時資料庫目前的狀態");
        Serial.println(firebaseData.boolData());
        digitalWrite(led,firebaseData.boolData());
      }
    }else{
      //設定失敗
      Serial.println("Firebase Touch錯誤:");
      Serial.println(firebaseData.errorReason());
    }
  }
}
