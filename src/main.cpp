#include <Arduino.h>

#include "alarme.h"
#include "clavier.h"
#include "screen.h"

Screen screen;
Clavier clavier;
Alarme alarme;

const uint8_t pinInterrupteur = 18;

char currentTime[9] = "12:00:00";
char alarmeTime[9] = "00:00:00";

uint8_t currentHour = 12;
uint8_t currentMinute = 0;
uint8_t currentSecond = 0;

unsigned long lastMillis = 0;
const long interval = 1000;

uint8_t editIndex = 0;
unsigned long lastBlink = 0;
bool blinkState = true;
const long blinkInterval = 400;

bool isSettingTime = false;
bool isSettingAlarm = false;

bool isOn() { return digitalRead(pinInterrupteur) == LOW; }

void UpdateTime() {
    if (isSettingTime || isSettingAlarm) {
        return;
    }

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

        sprintf(currentTime, "%02d:%02d:%02d", currentHour, currentMinute,
                currentSecond);
    }
}

void HandleBlink() {
    if (millis() - lastBlink >= blinkInterval) {
        lastBlink = millis();
        blinkState = !blinkState;
    }
}

void HandleKeypad() {
    char key = clavier.GetKey();
    if (!key) return;

    if (key == '#' && !isSettingTime && !isSettingAlarm) {
        isSettingTime = true;
        editIndex = 0;
        return;
    }

    if (key == '*' && !isSettingTime && !isSettingAlarm) {
        isSettingAlarm = true;
        editIndex = 0;
        return;
    }

    if (key == '#' && isSettingTime) {
        isSettingTime = false;
        sscanf(currentTime, "%hhu:%hhu:%hhu", &currentHour, &currentMinute,
               &currentSecond);
        return;
    }

    if (key == '*' && isSettingAlarm) {
        isSettingAlarm = false;
        return;
    }

    if ((isSettingTime || isSettingAlarm) && key >= '0' && key <= '9') {
        char* target = isSettingTime ? currentTime : alarmeTime;

        // Si on est sur ':', on saute
        if (editIndex == 2 || editIndex == 5) editIndex++;

        if (editIndex < 8) {
            target[editIndex] = key;
            editIndex++;
        }

        if (editIndex == 2 || editIndex == 5) editIndex++;

        // Fin de ligne
        if (editIndex >= 8) {
            if (isSettingTime) {
                sscanf(currentTime, "%hhu:%hhu:%hhu", &currentHour,
                       &currentMinute, &currentSecond);
            }

            isSettingTime = false;
            isSettingAlarm = false;
        }
    }
}

void Affichage() {
    HandleBlink();

    char tempTime[9];
    char tempAlarm[9];

    strcpy(tempTime, currentTime);
    strcpy(tempAlarm, alarmeTime);

    // Clignotement heure
    if (isSettingTime && !blinkState && editIndex < 8)
        tempTime[editIndex] = ' ';

    // Clignotement alarme
    if (isSettingAlarm && !blinkState && editIndex < 8)
        tempAlarm[editIndex] = ' ';

    char buffer_1[20];
    char buffer_2[20];

    sprintf(buffer_1, "--- %s ---", tempTime);
    sprintf(buffer_2, " !  %s  ! ", tempAlarm);

    screen.Show(0, 0, buffer_1);
    screen.Show(0, 1, buffer_2);
}

void CheckAlarm() {
    if (strcmp(currentTime, alarmeTime) == 0) {
        alarme.On();
    } else {
        alarme.Off();
    }
}

// ---------------- SETUP ----------------
void setup() {
    Serial.begin(115200);

    pinMode(pinInterrupteur, INPUT_PULLUP);

    screen.Init();
    alarme.Off();
}

// ---------------- LOOP ----------------
void loop() {
    if (!isOn()) {
        screen.Off();
        alarme.Off();
        return;
    }

    screen.On();

    UpdateTime();
    HandleKeypad();
    Affichage();
    CheckAlarm();
}