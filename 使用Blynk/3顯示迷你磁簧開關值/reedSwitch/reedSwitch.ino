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

#define ledPin 13
#define sensor_d12 12
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = AUTH;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = SSID;
char pass[] = PASS;

BlynkTimer timer;
WidgetLED led0(V0);
bool preValue = false;

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

void myTimerEvent() {
  bool sensorValue = digitalRead(sensor_d12);
  //必需調整,沒有磁鐵時,輸出為1
  Serial.println(sensorValue);
  if (sensorValue != preValue) {
    if (sensorValue == 0) {
      led0.on();
      digitalWrite(ledPin, HIGH);
    } else {
      led0.off();
      digitalWrite(ledPin, LOW);
    }
    preValue = sensorValue;
  }

}
