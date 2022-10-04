#define BUTTON_PIN 11
#define TRIG_PIN 3
#define ECHO_PIN 4 
#define US 58

unsigned long cm;
volatile int defaultDistance=0;

void setup() {  
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);  
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),buttonPress,LOW) ;
}

void buttonPress(){
  defaultDistance = ping()/US;
  Serial.println("預設"+String(cm)+"cm");
}

unsigned long ping(){
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);
  return pulseIn(ECHO_PIN, HIGH);
}

void loop() {
  cm = ping()/US;
  Serial.println(String(cm)+"cm");
  if(cm > defaultDistance+3 || cm < defaultDistance-3){
    Serial.println("有異物入侵");
  }
  delay(1000);
}
