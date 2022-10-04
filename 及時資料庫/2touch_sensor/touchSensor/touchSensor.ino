// Firebase
// 使用arduino nano 33 iot

/*
 *連線Firebase realtimeDatabase
 *touch sensor 狀態改變,立即上傳至firebase
*/

//Example shows how to connect to Firebase RTDB and perform basic operation for set, get, push and update data to database
//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define FIREBASE_AUTH "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa"
#define WIFI_SSID "robert_hsu_home"
#define WIFI_PASSWORD "0926656000"
#define led 13
#define touchSensor 12
//Define Firebase data object
FirebaseData firebaseData;
bool currentState;

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(touchSensor, INPUT);
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

  //Provide the autntication data
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
  //得第一次的currentState
  currentState = digitalRead(touchSensor);
}

 

void loop()
{
  bool state = digitalRead(touchSensor);
  String path = "touchSensor/touch";
  Serial.println(state);
  if(state != currentState){
    currentState = state;
    Serial.println("上傳");
    if(Firebase.setBool(firebaseData, path, state)){
      
      if(firebaseData.dataType() == "boolean"){
        Serial.print("及時資料庫目前的狀態");
        Serial.println(firebaseData.boolData());
        digitalWrite(led,firebaseData.boolData());
      }
    }else{
      //設定失敗
      Serial.println("Firbase設取失敗");
      Serial.println(firebaseData.errorReason());
    }
  }
  
  delay(10);
}
