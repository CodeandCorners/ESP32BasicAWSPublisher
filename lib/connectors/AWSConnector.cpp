#include "../config/config.h"
#include "AWSConnector.h"
#include "../models/ButtonPress.h"


void AWSConnector::setCerts() {

    wifiClient.setCACert(AWS_CERT_CA);
    wifiClient.setCertificate(AWS_CERT_CRT);
    wifiClient.setPrivateKey(AWS_CERT_PRIVATE);  
    client.begin(AWS_IOT_ENDPOINT, 8883, wifiClient);

}
void AWSConnector::connect() {

    wifiClient.stop();
    Serial.println("Opening TLS connection...");

    if (client.connect(DEVICE_NAME))
    {
        Serial.println("MQTT SUCCESS");
    }
    else
    {
        Serial.printf("MQTT FAILED (%d)\n", client.lastError());
    }
}

void AWSConnector::maintain() {
    client.loop();
};
bool AWSConnector::connected() {
    return client.connected();
};

void AWSConnector::printLastError() {

        int mqttErr = client.lastError();
        Serial.printf("MQTT Client Error Code: %d\n", mqttErr);

        char errorBuf[100];

        mbedtls_strerror(mqttErr, errorBuf, sizeof(errorBuf));
        Serial.printf("Translated SSL Reason: %s\n", errorBuf);
}

bool AWSConnector::publishOne(AWSEvent awsEvent) {
    String payload = awsEvent.toJson();
    Serial.println(payload);
    
    bool success = client.publish(MQTT_PUB_TOPIC, payload.c_str(),false, 0);

    if (!success) {
        Serial.println("Failed to publish single event.");
        printLastError();
    }
    return success;
}