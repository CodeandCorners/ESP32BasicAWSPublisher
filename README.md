# ESP32 publisher via button press

This is a service that is intended to be loaded on an ESP32 dev device, minor tweaks may be required if variant of esp32.

## Flow
- Connect ESP32 to button
- Ensure AWS MQTT has been setup for a new device (advise follow wizard and download connection kit for certs)
- Ensure policies have been tweaked to allow connectivity and publishing
- Rename config.example.h to config.h
- Ensure that config.h has been updated with all WIFI values & all AWS MQTT values
- "Upload and monitor" this repo with config.h to ESP32
- User clicks button 1 time within 1 second, an event is eventually published to AWS Topic containing amount of clicks
- User clicks button 2 times within 1 second, an event is eventually published to AWS Topic containing amount of clicks
- and so on


## Technical detail
- If wifi drops, it will continually attempt to reconnect
- If AWS connection drops, it will continually attempt to reconnect
- Time on ESP32 is setup via common NTP
- 2 offline queue's exist on the device, which can be updated regardless of current connectivity to wifi/AWS
- Any Queued messages that are not sent are lost if device loses power
  

## Setup

- config.h needs creating from config.example.h
- AWS IOT "thing" needs creating, connection kit downloading
- AWS MQTT policies for connecting and publishing need to be set correctly
- Config setting as per above


## Hardware
| Component             | Module Pin | ESP32 Pin |
| --------------------- | ---------- | --------- |
| **Button**            | VCC        | 3V3       |
|                       | GND        | GND       |
|                       | DO         | GPIO 4    |



## Arduino notes 
- LOW == ON == 0
- HIGH == OFF == 1
