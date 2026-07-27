#include "Button.h"
#include <Arduino.h>    

void Button::connect() {
    pinMode(pin, INPUT_PULLUP);
};


bool Button::isButtonPressed() {
  static int lastRawState = HIGH;
  static int debouncedState = HIGH;
  static uint64_t lastDebounceTime = 0;
  
  int currentRawState = digitalRead(pin);
  bool pressDetected = false;

  if (currentRawState != lastRawState) {
    lastDebounceTime = millis(); // Reset noise timer
  }

  if ((millis() - lastDebounceTime) > 50) { // 50ms threshold
    if (currentRawState != debouncedState) {
      debouncedState = currentRawState;
      if (debouncedState == LOW) { // Active-LOW transition
        pressDetected = true;
      }
    }
  }

  lastRawState = currentRawState;
  return pressDetected;
}