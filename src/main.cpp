#include <Arduino.h>
#include "../lib/connectors/AWSConnector.h"
#include "../lib/connectors/WIFIConnector.h"
#include "../lib/connectors/NTPTimeConnector.h"

WIFIConnector wifiConnector;
AWSConnector awsConnector;
NTPTimeConnector ntpTimeConnector;


void setup() {
wifiConnector.connect();
ntpTimeConnector.set();
awsConnector.connect();
}

void loop() {
  // put your main code here, to run repeatedly:
}
