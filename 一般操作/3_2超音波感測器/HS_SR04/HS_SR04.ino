#include "releaseButton.h"
#include "sr104.h"
#include <SimpleTimer.h>
#define BUTTON 11
#define TRIG_PIN 3
#define ECHO_PIN 4



unsigned int stateChangeCount = 0;
bool runOnce = false;
SimpleTimer timer;
int timerid;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  timerid = timer.setInterval(1000,oneSecond);
  timer.disable(timerid);
}

void loop() {
  timer.run();
  stateChangeCount += button_release(BUTTON);  
  bool switchState = displayNum(stateChangeCount,1);//得到0或1,0為關閉,1為開啟
  if(switchState){
    //開啟
    buttonOpen();
  }else{
    //關閉
    buttonClose();
  }
}

void buttonOpen(){
  if(runOnce == false){ //只會執行一次
    runOnce = true;   
    timer.enable(timerid);
    Serial.println("開啟");  
  }
}

void buttonClose(){
  if(runOnce == true){ //只會執行一次
    runOnce = false;
    timer.disable(timerid);
    Serial.println("關閉");
  } 
}

void oneSecond(){
   int distance = getDistanceCM(TRIG_PIN,ECHO_PIN);
   Serial.println(distance);
}
