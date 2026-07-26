#pragma once

#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include "../models/ButtonPress.h"

class AWSConnector {
    public:
        void connect();
        bool connected();
        bool publishOne(ButtonPress press);
        void maintain();
        void printLastError();
        void setCerts();
    private:
    WiFiClientSecure wifiClient = WiFiClientSecure();
    const int bufferSize = 1024;
    MQTTClient client = MQTTClient(bufferSize);
};