// Firebase
// 使用arduino nano 33 iot

/*
 *連線Firebase realtimeDatabase
 *get節點資料
*/

//Example shows how to connect to Firebase RTDB and perform basic operation for set, get, push and update data to database
//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "arduinofirebase-6d104.firebaseio.com"
#define FIREBASE_AUTH "z5lPWwjZLZuNNcUEelbJdiNaIvnR2Zfq49BuQBAa"
#define WIFI_SSID "robert_hsu_home"
#define WIFI_PASSWORD "0926656000"
#define led 13
//Define Firebase data object
FirebaseData firebaseData;

void setup()
{
  pinMode(led,OUTPUT);
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
}

 

void loop()
{
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
     Serial.println(firebaseData.errorReason());
  }  
  delay(500);
}
