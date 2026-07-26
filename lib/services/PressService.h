#pragma once
#include "ButtonQueue.h"
#include "../hardware/Button.h"
#include "../connectors/AWSConnector.h"
class PressService{
    public:
        explicit PressService(ButtonQueue& bq, Button& button1, AWSConnector& aws): bq(bq), button1(button1), aws(aws){};
         void checkAndPush();
         void checkAndPublish();
    private:
        ButtonQueue& bq;
        Button& button1;
        AWSConnector& aws;
};