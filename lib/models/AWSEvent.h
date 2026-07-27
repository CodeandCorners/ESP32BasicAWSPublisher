#pragma once
#include <ArduinoJson.h>

struct AWSEvent {
    uint64_t epochNowMs;
    const char* buttonName;
    int clicks;

    String toJson() const {
        JsonDocument doc;
        doc["timestamp_ms"] = epochNowMs;
        doc["buttonName"] = buttonName;
        doc["clicks"]  = clicks;

        String output;
        serializeJson(doc, output);
        return output;
    }
};