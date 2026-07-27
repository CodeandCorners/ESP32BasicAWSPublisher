#include "PressService.h"
#include "../models/ButtonPress.h"
#include "../models/AWSEvent.h"
#include <optional>

void PressService::checkAndPush() {
    std::vector<ButtonPress> itemsToConvert = bq.getItemsGroupedByTime();
    int amount = itemsToConvert.size();
    if (amount > 0) {
        AWSEvent awsEvent = AWSEvent{itemsToConvert.front().epochNowMs, itemsToConvert.front().pinName, amount};
        Serial.println("PressService checkAndPush");
        aq.push(awsEvent);
    }
};

void PressService::checkAndPublish() {
    std::optional<AWSEvent> awsEvent = aq.get();
    if(awsEvent.has_value()) {
         Serial.println("PressService Published to AWS");
        aws.publishOne(awsEvent.value());
    } else {}
};