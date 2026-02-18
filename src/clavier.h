#ifndef CLAVIER_H
#define CLAVIER_H

#include <Arduino.h>
#include <Keypad.h>

class Clavier {
 public:
  Clavier();
  char GetKey();
  bool IsSettingTime();
  bool IsSettingAlarm();

 private:
  static const byte ROWS = 4;
  static const byte COLS = 3;

  char keys[ROWS][COLS] = {
      {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};

  byte rowPins[ROWS] = {32, 33, 25, 26};
  byte colPins[COLS] = {27, 14, 12};

  Keypad keypad;
  bool isSettingTime;
  bool isSettingAlarm;
};

#endif
