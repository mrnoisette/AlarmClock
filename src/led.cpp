#include <Arduino.h>
#include "led.h"

void BlinkLed(int ledPin, int times, int delayTime)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
    digitalWrite(ledPin, LOW);
    delay(delayTime);
  }
}
