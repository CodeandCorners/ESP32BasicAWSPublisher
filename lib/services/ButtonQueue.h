#pragma once
#include "../models/ButtonPress.h"
#include <Arduino.h>

class ButtonQueue {
    public:
        ButtonPress get();
        void push(ButtonPress bp);
    private:
        std::vector<ButtonPress> queue;
};