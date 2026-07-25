#pragma once
#include "../models/ButtonPress.h"
#include <Arduino.h>
#include <optional>
class ButtonQueue {
    public:
        std::optional<ButtonPress> get();
        void push(ButtonPress bp);
    private:
        std::vector<ButtonPress> queue;
};