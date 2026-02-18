#include "display.h"

const uint8_t SDA_PIN = 21;
const uint8_t SCL_PIN = 22;
const uint8_t LCD_ADDR = 0x27;
const uint8_t LCD_COLS = 16;
const uint8_t LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void Display::On() {
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
}

void Display::Off(){
  lcd.off();
}

void Display::Show(uint8_t col, uint8_t row, const char* text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void Display::Clear() { lcd.clear(); }
