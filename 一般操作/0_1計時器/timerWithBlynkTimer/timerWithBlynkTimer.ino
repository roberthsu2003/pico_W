//BlynkTimer timer是一個softwareTimer,受delay()影響
#include <BlynkSimpleWiFiNINA.h>
#define ledPin  LED_BUILTIN
BlynkTimer timer;
bool ledState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  timer.run();
}

void myTimerEvent()
{
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}
