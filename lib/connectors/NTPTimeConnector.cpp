#include <Arduino.h>
#include "NTPTimeConnector.h"


void NTPTimeConnector::set(){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
};