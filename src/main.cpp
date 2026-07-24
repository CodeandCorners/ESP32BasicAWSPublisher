#include <Arduino.h>
#include "../lib/connectors/AWSConnector.h"
#include "../lib/connectors/WIFIConnector.h"
#include "../lib/connectors/NTPTimeConnector.h"

WIFIConnector wifiConnector;
AWSConnector awsConnector;
NTPTimeConnector ntpTimeConnector;
const long delayBeforeTryingWifi = 500;
const long delayBeforeTryingAWS = 500;

long reconnectWifi(long& lastProblemWithWifi) {
  long now = millis();
  if(now - lastProblemWithWifi > delayBeforeTryingWifi) {
      Serial.println("Main, trying to reconnect to WIFI");
      wifiConnector.connect();
      return now;
    } else {
      Serial.println("Main, WIFI isn't connected but will not attempt right now");
       return now;
    }
};
long reconnectAWS(long& lastProblemWithAWS) {
  long now = millis();
  if(now - lastProblemWithAWS > delayBeforeTryingAWS) {
      Serial.println("Main, trying to reconnect to AWS");
      awsConnector.connect();
      return now;
    } else {
      Serial.println("Main, WIFI isn't connected but will not attempt right now");
       return now;
    }
};

void setup() {
  Serial.begin(115200);
  wifiConnector.connect();
  ntpTimeConnector.set();
  awsConnector.connect();
  Serial.println("Intial setup complete, wifi, ntp aws connected");
}


void loop() {
  long lastProblemWithWifi = 0;
  long lastProblemWithAWS = 0;
  if (!wifiConnector.connected()) {
    lastProblemWithWifi = reconnectWifi(lastProblemWithWifi);
  } else if (!awsConnector.connected()) {
    lastProblemWithAWS = reconnectAWS(lastProblemWithAWS);
  } else {
    // main logic here 

  }
}
