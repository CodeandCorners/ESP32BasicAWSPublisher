#pragma once

class NTPTimeConnector{
    public:
        void set();
    private:
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 0;
        const int   daylightOffset_sec = 3600;
};