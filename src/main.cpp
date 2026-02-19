#include <Arduino.h>

#include "alarme.h"
#include "clavier.h"
#include "screen.h"

Screen screen;
Clavier clavier;
Alarme alarme;

// Time & alarm
char currentTime[9] = "00:00:00";
char alarmeTime[9] = "00:00:00";

uint8_t currentHour = 0;
uint8_t currentMinute = 0;
uint8_t currentSecond = 0;

unsigned long lastMillis = 0;
const long interval = 1000;

long lastBlinkMillis = 0;
long blinkInterval = 500;
bool isBlinking = false;

// Pin interrupteur
const uint8_t pinInterrupteur = 18;

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  // Pins
  pinMode(pinInterrupteur, INPUT_PULLUP);

  // Ecran
  screen.Init();

  // Alarme off au démarrage
  alarme.Off();
}

bool isSettingTime = false;
bool isSettingAlarm = false;
char lastKeyPressed;

bool IsPowered() { return digitalRead(pinInterrupteur) == LOW; }

void HandlePower() {
  if (IsPowered()) {
    screen.On();
  } else {
    screen.Off();
    alarme.Off();
  }
}

void UpdateTime() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= interval) {
    lastMillis = currentMillis;

    currentSecond++;
    if (currentSecond == 60) {
      currentSecond = 0;
      currentMinute++;
    }
    if (currentMinute == 60) {
      currentMinute = 0;
      currentHour++;
    }
    if (currentHour == 24) {
      currentHour = 0;
    }

    // Format
    sprintf(currentTime, "%02d:%02d:%02d", currentHour, currentMinute,
            currentSecond);
  }
}

void HandleKeypad() {
  char key = clavier.GetKey();

  if (key == '#' && !isSettingTime && !isSettingAlarm) {
    isSettingTime = true;
  } else if (key == '*' && !isSettingTime && !isSettingAlarm) {
    isSettingAlarm = true;
  } else if (key == '#' && isSettingTime) {
    isSettingTime = false;
  } else if (key == '*' && isSettingAlarm) {
    isSettingAlarm = false;
  }
}

void UpdateBlink() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkMillis >= blinkInterval) {
    lastBlinkMillis = currentMillis;
    isBlinking = !isBlinking;
  }
}

void DisplayScreen() {
  bool isSetting = isSettingTime || isSettingAlarm;

  if (isSetting) {
    UpdateBlink();
  } else {
    isBlinking = true;  // toujours visible hors réglage
  }

  char buffer1[20];
  char buffer2[20];

  // Ligne heure
  if (isSettingTime && !isBlinking) {
    sprintf(buffer1, "                ");
  } else {
    sprintf(buffer1, "--- %s ---", currentTime);
  }

  // Ligne alarme
  if (isSettingAlarm && !isBlinking) {
    sprintf(buffer2, "                ");
  } else {
    sprintf(buffer2, " !  %s  ! ", alarmeTime);
  }

  screen.Show(0, 0, buffer1);
  screen.Show(0, 1, buffer2);
}

void CheckAlarm() {
  if (strcmp(currentTime, alarmeTime) == 0) {
    alarme.On();
  } else {
    alarme.Off();
  }
}

// --- LOOP ---
void loop() {
  HandlePower();
  if (!IsPowered()) return;

  UpdateTime();
  HandleKeypad();
  DisplayScreen();
  CheckAlarm();
}
