#ifndef ALARME_H
#define ALARME_H

#include <Arduino.h>

class Alarme {
 public:
    void On();
    void Off();

 private:
  const uint8_t PIN = 19;
};

#endif