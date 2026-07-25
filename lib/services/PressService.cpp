#include "PressService.h"
#include "../models/ButtonPress.h"
#include <optional>

void PressService::checkAndPush() {
    if (button1.isButtonPressed()) {
        long now = millis();
        ButtonPress bp = ButtonPress{now};
        Serial.println("PressService Pushed button press to queue");
        bq.push(bp);
    }
};

void PressService::checkAndPublish() {
    std::optional<ButtonPress> bp = bq.get();
    if(bp.has_value()) {
        aws.publishOne(bp.value());
        Serial.println("PressService Published button press to AWS");
    }
};
