#pragma once
#include <Arduino.h>

// *****
// Generic ESP32
// *****

// SUGGEST PHONE TETHER
constexpr const char* WIFI_SSID = "WIFI NAME";
constexpr const char* WIFI_PASS = "WIFI PASSWORD";

// *****
// AWS
// *****

// From connection kit Shell script, its the ats one, i.e. FOOBAR-ats.iot.eu-west-2.amazonaws.com
constexpr const char* AWS_IOT_ENDPOINT = "FOOBAR-ats.iot.eu-west-2.amazonaws.com";
constexpr const char* MQTT_PUB_TOPIC = "esp32/simple";
constexpr const char* DEVICE_NAME = "ESP32Sender";
//From connection kit AmazonRootCA1.pem
// Login and then go to https://www.amazontrust.com/repository/AmazonRootCA1.pem
constexpr static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
FOOBAR
-----END CERTIFICATE-----
)EOF";
// From connection kit xxx.cert.pem (or xxx-certificate.pem.crt)
constexpr static const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
FOOBAR
-----END CERTIFICATE-----
)EOF";

// From connection kit Private Key ("xxx.private.key")
constexpr static const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
FOOBAR
-----END RSA PRIVATE KEY-----
)EOF";
