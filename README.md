# ESP32 publisher via button press

This is a service that is intended to be loaded on an ESP32 dev device, minor tweaks may be required if variant of esp32.

## Flow
- Connect ESP32 to button
- Ensure AWS MQTT has been setup for a new device (advise follow wizard and download connection kit for certs)
- Ensure policies have been tweaked to allow connectivity and publishing
- Rename config.example.h to config.h
- Ensure that config.h has been updated with all WIFI values & all AWS MQTT values
- "Upload and monitor" this repo with config.h to ESP32
- User clicks button 1 time within 2 seconds, an event is eventually published to AWS Topic containing amount of clicks
- User clicks button 2 times within 2 seconds, an event is eventually published to AWS Topic containing amount of clicks
- and so on


## Technical detail
- If wifi drops, it will continually attempt to reconnect
- If AWS connection drops, it will continually attempt to reconnect
- Time on ESP32 is setup via common NTP
- 2 offline queue's exist on the device, which can be updated regardless of current connectivity to wifi/AWS
- Any Queued messages that are not sent are lost if device loses power


## Key config
- Button Queue.timeMsBufferForEvents, how long you want before and after a click to accumulate click counts before sending
- main; delayBeforeTryingWifi, delayBeforeTryingAWS. reconnection magic, These can be amended, but I'd recommend leaving as is
- main; delayBeforePublishing - how often we publish to AWS, I think this is fine based on usage, if you want to send 1 event more often than this time, this time needs to be increased. Its natural throttling to save $
- main; button1 pin = 4, can be changed to correspond to different GPIO usage on board

## Hardware
| Component             | Module Pin | ESP32 Pin |
| --------------------- | ---------- | --------- |
| **Button**            | VCC        | 3V3       |
|                       | GND        | GND       |
|                       | DO         | GPIO 4    |



## Arduino notes 
- LOW == ON == 0
- HIGH == OFF == 1


## Notes
- one small bug, startup it registers the button as low and sends a message
