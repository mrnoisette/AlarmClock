#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class Screen {
 public:
  void Init();
  void On();
  void Off();
  void Show(uint8_t col, uint8_t row, const char* text);
  void Clear();

 private:
  const uint8_t SDA_PIN = 21;
  const uint8_t SCL_PIN = 22;
  const uint8_t LCD_ADDR = 0x27;
  const uint8_t COLS = 16;
  const uint8_t ROWS = 2;
  LiquidCrystal_I2C lcd{LCD_ADDR, COLS, ROWS};
};

#endif
