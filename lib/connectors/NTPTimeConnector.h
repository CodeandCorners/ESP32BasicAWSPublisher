#pragma once

class NTPTimeConnector{
    public:
        void set();
        bool isTimeSet();
    private:
        const char* ntpServer = "pool.ntp.org";
        const char* timezone = "GMT0BST,M3.5.0/1,M10.5.0/2";
};