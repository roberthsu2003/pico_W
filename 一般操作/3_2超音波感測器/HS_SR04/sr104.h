#ifndef __SR104_H__
#define __SR104_H__
#define USECOND 58

#include <arduino.h>

int getDistanceCM(byte trigPin, byte echoPin){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  unsigned long backTime = pulseIn(echoPin,HIGH);
  int distance = backTime / USECOND;
  return distance;
}

#endif
