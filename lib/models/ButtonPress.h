#pragma once
#include <Arduino.h>

struct ButtonPress {
    uint64_t epochNowMs;
    const char* pinName;
};