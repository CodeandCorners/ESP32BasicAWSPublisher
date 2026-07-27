#pragma once

#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include "../models/AWSEvent.h"

class AWSConnector {
    public:
        void connect();
        bool connected();
        bool publishOne(AWSEvent awsEvent);
        void maintain();
        void printLastError();
        void setCerts();
    private:
    WiFiClientSecure wifiClient = WiFiClientSecure();
    const int bufferSize = 1024;
    MQTTClient client = MQTTClient(bufferSize);
};