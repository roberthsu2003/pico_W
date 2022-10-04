#define ledPin  LED_BUILTIN

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  blinkOfLed();
}

void blinkOfLed() {
  static int ledState = LOW;
  static unsigned long previousMillis = 0;
  const long interval = 1000;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;


    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
