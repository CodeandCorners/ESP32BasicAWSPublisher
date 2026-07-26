#include "../config/config.h"
#include "WIFIConnector.h"
#include <WiFi.h>

void WIFIConnector::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to Wi-Fi");
  while (!connected()) {
    Serial.print(".");
  }
};
void WIFIConnector::reconnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
};

bool WIFIConnector::connected() {
 return WiFi.status() == WL_CONNECTED; 
}