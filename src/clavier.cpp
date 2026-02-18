#include "clavier.h"

// Construteur
Clavier::Clavier() : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {}

// Retourne la touche préssée
char Clavier::GetKey() {
  char key = keypad.getKey();
  return key;
}
