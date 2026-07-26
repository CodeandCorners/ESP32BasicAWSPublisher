#include <Arduino.h>
#include "NTPTimeConnector.h"


void NTPTimeConnector::set(){
    Serial.println("Setting time");
    configTzTime(timezone, ntpServer);
    if(!isTimeSet()) {
        Serial.print("NTP_SETTING_TIME");
        delay(500);
    }
};

bool NTPTimeConnector::isTimeSet(){
    struct tm timeinfo;
    // Returns false if NTP hasn't responded yet (year will be 1970)
    if (!getLocalTime(&timeinfo)) {
        return false;
    }
    return timeinfo.tm_year > (2020 - 1900);
}