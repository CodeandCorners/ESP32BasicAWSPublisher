#pragma once
#include <Arduino.h>

class Button {
    public:
        explicit Button(int pin): pin(pin){};
        void connect();
        bool isButtonPressed();
    private:
        const int pin;

        int lastRawState = HIGH;
        int debouncedState = HIGH;
        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 50; // ms
};