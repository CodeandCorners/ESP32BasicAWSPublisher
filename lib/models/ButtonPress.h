#pragma once
#include <ArduinoJson.h>

struct ButtonPress {
    int epochNowMilli;


    String toJson() const {
        JsonDocument doc;
        doc["timestamp_ms"] = epochNowMilli;

        String output;
        serializeJson(doc, output);
        return output;
    }
};