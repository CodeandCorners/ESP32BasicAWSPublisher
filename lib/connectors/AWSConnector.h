#pragma once

#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include "../models/ButtonPress.h"

class AWSConnector {
    public:
        void connect();
        bool connected();
        bool publishOne(ButtonPress press);
    private:
    WiFiClientSecure wifiClient = WiFiClientSecure();
    const int bufferSize = 256;
    MQTTClient client = MQTTClient(bufferSize);
};