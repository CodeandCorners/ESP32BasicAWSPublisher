#pragma once
#include <Arduino.h>

class Button {
    public:
        explicit Button(int pin, const char* name): pin(pin), pinName(name){};
        void connect();
        bool isButtonPressed();
        const char* getPinName() const { return pinName;};

    private:
        const int pin;
        const char* pinName;
        // Individual press logic
        int lastRawState = HIGH;
        int debouncedState = HIGH;
        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 50; // ms
};