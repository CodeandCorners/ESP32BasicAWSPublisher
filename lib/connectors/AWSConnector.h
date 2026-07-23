#pragma once

#include <WiFiClientSecure.h>
#include <MQTTClient.h>

class AWSConnector {
    public:
        void connect();
    private:
    WiFiClientSecure wifiClient = WiFiClientSecure();
    const int bufferSize = 256;
    MQTTClient client = MQTTClient(bufferSize);
};