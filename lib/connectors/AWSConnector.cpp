#include "../config/config.h"
#include "AWSConnector.h"
#include "../models/ButtonPress.h"

void AWSConnector::connect() {
  wifiClient.setCACert(AWS_CERT_CA);
  wifiClient.setCertificate(AWS_CERT_CRT);
  wifiClient.setPrivateKey(AWS_CERT_PRIVATE);  
  client.begin(AWS_IOT_ENDPOINT, 8883, wifiClient);
  client.connect(DEVICE_NAME);
};

bool AWSConnector::connected() {
    return client.connected();
};

bool AWSConnector::publishOne(ButtonPress press) {
    String payload = press.toJson();
    
    // client.publish expects const char* for topic and payload
    bool success = client.publish(MQTT_PUB_TOPIC, payload.c_str());

    if (!success) {
        Serial.println("Failed to publish single event.");
    }
    return success;
}