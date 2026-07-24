#include <Arduino.h>
class Button {
    public:
        void connect();
        bool isButtonPressed();
    private:
        int pin;
        const unsigned long DEBOUNCE_DELAY = 50; // 50 milliseconds debounce tim
};