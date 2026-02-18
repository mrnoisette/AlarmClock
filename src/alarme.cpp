#include "alarme.h"

Alarme::Alarme() {
  pinMode(PIN, OUTPUT);
  Off();
}

void Alarme::On() { digitalWrite(PIN, LOW); }

void Alarme::Off() { digitalWrite(PIN, HIGH); }