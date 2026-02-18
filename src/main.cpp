#include <Arduino.h>

#include "clavier.h"
#include "display.h"
#include "alarme.h"

const byte pinInterrupteur = 18;
const byte pinAlarme = 19;

Display display;
Clavier clavier;
Alarme alarme;

String currentTime = "00:00:00";
byte currentHour = 0;
byte currentMinute = 0;
byte currentSecond = 0;

String alarmTime = "00:00:00";

void setup() {
  Serial.begin(115200);

  // Pins
  pinMode(pinInterrupteur, INPUT_PULLUP);

  // Ecran
  display.On();

  // Alarme off au démarrage
  digitalWrite(pinAlarme, HIGH);
}

String buffer1;
String buffer2;

void loop() {
  if (digitalRead(pinInterrupteur) == HIGH) {  // Eteint
    display.Off();
    return;
  }

  currentTime = String(currentHour) + ":" + String(currentMinute) + ":" +
                String(currentSecond);

  if (clavier.IsSettingTime()) {  // Reglage de l'heure

    display.Clear();
    display.Show(0, 1, "Reglage heure :");

  } else if (clavier.IsSettingAlarm()) {  // Reglage de l'alarme

    display.Clear();
    display.Show(0, 1, "Reglage alarme :");

  } else {
    buffer1 = "Heure : " + currentTime;
    display.Show(0, 0, buffer1.c_str());

    buffer2 = "Alarme : " + alarmTime;
    display.Show(0, 1, buffer2.c_str());
  }

  /*
  if (digitalRead(pinInterrupteur) == LOW) {  // Alarme
    digitalWrite(pinAlarme, LOW);
  } else {
    digitalWrite(pinAlarme, HIGH);
  }
  */
}

void SetAlarm(int time) {}
