#include <Arduino.h>

#include "alarme.h"
#include "clavier.h"
#include "screen.h"

Screen screen;
Clavier clavier;
Alarme alarme;

// Time & alarm
char currentTime[9] = "00:00:00";
char alarmTime[9] = "00:00:00";

uint8_t currentHour = 0;
uint8_t currentMinute = 0;
uint8_t currentSecond = 0;

unsigned long lastMillis = 0;
const long interval = 1000;

const long lastBlinkMillis = 0;
const long blinkInterval = 500;
bool isBlinking = false;

// Pin interrupteur
const uint8_t pinInterrupteur = 18;

void setup() {
  Serial.begin(115200);

  // Pins
  pinMode(pinInterrupteur, INPUT_PULLUP);

  // Ecran
  screen.Init();

  // Alarme off au démarrage
  alarme.Off();
}

void loop() {
  if (digitalRead(pinInterrupteur) == HIGH) {  // Eteint
    screen.Off();
    alarme.Off();
    return;
  } else {  // Allumé
    screen.On();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= interval) {  // Update time
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

  char key = clavier.GetKey();  // Update clavier
  if (key == '*') {             // Reglage de l'heure

    } else if (key == '#') {  // Reglage de l'alarme

  } else {
    char buffer1[20];
    sprintf(buffer1, "--- %s ---", currentTime);
    screen.Show(0, 0, buffer1);

    char buffer2[20];
    sprintf(buffer2, " !  %s  ! ", alarmTime);
    screen.Show(0, 1, buffer2);
  }

  if (strcmp(currentTime, alarmTime) == 0) {  // Alarme
    alarme.On();
  } else {
    alarme.Off();
  }
}
