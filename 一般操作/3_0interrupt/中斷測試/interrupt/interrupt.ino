

#define LIGHT_PIN 5
#define WIRE_PIN 11

volatile bool state = LOW;

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(WIRE_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIRE_PIN),blinkme,CHANGE) ;
}

void blinkme() {
  state = !state;
  digitalWrite(LIGHT_PIN, state); // Display the state 
  Serial.println("HELLO!"); 
}

void loop(){

}
