#include <Arduino.h>
#include "../lib/connectors/AWSConnector.h"
#include "../lib/connectors/WIFIConnector.h"
#include "../lib/connectors/NTPTimeConnector.h"
#include "../lib/hardware/Button.h"
#include "../lib/services/ButtonQueue.h"
#include "../lib/services/AWSQueue.h"
#include "../lib/services/PressService.h"

WIFIConnector wifiConnector;
NTPTimeConnector ntpTimeConnector;
Button button1(4, "mainButton1");
ButtonQueue buttonQueue(button1);
AWSQueue awsQueue;
AWSConnector awsConnector;
PressService pressService(buttonQueue, awsQueue, awsConnector);


const long delayBeforeTryingWifi = 5000;
const long delayBeforeTryingAWS = 1000;
const long delayBeforePublishing = 5000;
      uint64_t lastProblemWithWifi = 0;
      uint64_t lastProblemWithAWS = 0;
      uint64_t lastPublish = 0;

long reconnectWifi(uint64_t lastProblem) {
  uint64_t now = millis();
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
long reconnectAWS(uint64_t lastProblem) {
  Serial.println("Not connected to AWS");
  uint64_t now = millis();
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

uint64_t publishLoop(uint64_t lastPub) {
  uint64_t now = millis();

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
  buttonQueue.checkAndPush();
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
