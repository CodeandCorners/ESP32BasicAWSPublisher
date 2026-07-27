#pragma once
#include "../models/ButtonPress.h"
#include "../hardware/Button.h"
#include <Arduino.h>
#include <optional>
class ButtonQueue {
    public:
        explicit ButtonQueue(Button& button1): button1(button1){};
        std::vector<ButtonPress> getItemsGroupedByTime();
        void checkAndPush();
    private:
        std::vector<ButtonPress> queue;

        void push(ButtonPress bp);
        uint64_t getNowMs();
        const int timeMsBufferForEvents = 1000;
        Button& button1;
};