#pragma once
#include "../models/AWSEvent.h"
#include <Arduino.h>
#include <optional>

class AWSQueue {
    public:
        std::optional<AWSEvent> get();
        void push(AWSEvent bp);
    private:
        std::vector<AWSEvent> queue;
};