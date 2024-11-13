#include "LEDController.h"
#include <Arduino.h>

LEDController::LEDController(const int PINS[], int count) : LEDPINS(PINS), ledCount(count) {
  for (int i = 0; i < ledCount; i++) {
    pinMode(LEDPINS[i], OUTPUT);
  }
}

void LEDController::turnOffAll() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(LEDPINS[i], LOW);
  }
}

void LEDController::setLEDsBasedOnDistance(int distance) {
  turnOffAll(); 
  int numLEDsToLight = (distance <= 10) ? 4 :
                       (distance <= 20) ? 3 :
                       (distance <= 30) ? 2 :
                       (distance <= 40) ? 1 : 0;
  for (int i = 0; i < numLEDsToLight; i++) {
    digitalWrite(LEDPINS[i], HIGH);
  }
}

