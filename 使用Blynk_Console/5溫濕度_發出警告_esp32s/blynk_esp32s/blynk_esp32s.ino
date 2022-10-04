#define BLYNK_PRINT Serial
#include "data.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define LIGHTS 36


/* Fill-in your Template ID (only if using Blynk.Cloud) */



// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = ID;
char pass[] = PASS;

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100, myTimerEvent); 
}

void loop()
{
  Blynk.run();
  timer.run();
}

void myTimerEvent() {
    int lightValue = analogRead(LIGHTS);
    byte percentValue = map(lightValue,70,3700,0,100);      
    Blynk.virtualWrite(V0,percentValue);   
    
}
