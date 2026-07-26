# ESP32 publisher from button press

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
