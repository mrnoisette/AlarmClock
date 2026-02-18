#include "clavier.h"

// Construteur
Clavier::Clavier()
    : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS),
      isSettingTime(false),
      isSettingAlarm(false) {}

// Retourne la touche préssée
char Clavier::GetKey() {
  char key = keypad.getKey();
  if (key == '*') {
    isSettingTime = true;
    isSettingAlarm = false;
  } else if (key == '#') {
    isSettingAlarm = true;
    isSettingTime = false;
  }

  return key;
}

// Retourne true si on est en train de régler l'heure
bool Clavier::IsSettingTime() { return isSettingTime; }

// Retourne true si on est en train de régler l'alarme
bool Clavier::IsSettingAlarm() { return isSettingAlarm; }
