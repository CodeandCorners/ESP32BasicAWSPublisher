#include <Arduino.h>
#include "../lib/connectors/AWSConnector.h"
#include "../lib/connectors/WIFIConnector.h"
#include "../lib/connectors/NTPTimeConnector.h"
#include "../lib/hardware/Button.h"
#include "../lib/services/ButtonQueue.h"
#include "../lib/services/PressService.h"

WIFIConnector wifiConnector;
NTPTimeConnector ntpTimeConnector;
Button button1(4);
ButtonQueue buttonQueue;
AWSConnector awsConnector;
PressService pressService(buttonQueue, button1, awsConnector);


const long delayBeforeTryingWifi = 5000;
const long delayBeforeTryingAWS = 1000;
const long delayBeforePublishing = 5000;
      long lastProblemWithWifi = 0;
      long lastProblemWithAWS = 0;
      long lastPublish = 0;

long reconnectWifi(long lastProblem) {
  long now = millis();
    Serial.println("Not connected to WIFI");
  if(now - lastProblem > delayBeforeTryingWifi) {
      Serial.println("Main, trying to reconnect to WIFI");
      wifiConnector.reconnect();
      return now;
    } else {
      Serial.println("Main, WIFI isn't connected but will not attempt right now");
       return lastProblem;
    }
};
long reconnectAWS(long lastProblem) {
  Serial.println("Not connected to AWS");
  long now = millis();
  if(now - lastProblem > delayBeforeTryingAWS) {
      Serial.println("Main, trying to reconnect to AWS");
      awsConnector.connect();
      awsConnector.printLastError();
      return now;
    } else {
  
      Serial.println("Main, AWS isn't connected but will not attempt right now");
       return lastProblem;
    }
};

long publishLoop(long lastPub) {
  long now = millis();

  if((now - lastPub) > delayBeforePublishing) {
    pressService.checkAndPublish();
      return now;
    } else {
      return lastPub;
    }
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  wifiConnector.connect();
  ntpTimeConnector.set();
  delay(2000);
  awsConnector.setCerts();
  delay(2000);
  awsConnector.connect(); 
  delay(5000);
  Serial.println("Intial setup complete, wifi, ntp aws connected");
}

void loop() {
  pressService.checkAndPush();

  if (!wifiConnector.connected()) {
    lastProblemWithWifi = reconnectWifi(lastProblemWithWifi);
  } else if (!awsConnector.connected()) {
    lastProblemWithAWS = reconnectAWS(lastProblemWithAWS);
  } else {
    awsConnector.maintain();
    lastPublish = publishLoop(lastPublish);
  }
}
