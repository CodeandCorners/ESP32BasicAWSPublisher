#include "../config/config.h"
#include "AWSConnector.h"

void AWSConnector::connect() {
  wifiClient.setCACert(AWS_CERT_CA);
  wifiClient.setCertificate(AWS_CERT_CRT);
  wifiClient.setPrivateKey(AWS_CERT_PRIVATE);  
  client.begin(AWS_IOT_ENDPOINT, 8883, wifiClient);
  client.connect("SimpleESP32Publisher");
};