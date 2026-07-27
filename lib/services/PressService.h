#pragma once
#include "ButtonQueue.h"
#include "AWSQueue.h"
#include "../hardware/Button.h"
#include "../connectors/AWSConnector.h"
class PressService{
    public:
        explicit PressService(ButtonQueue& bq, AWSQueue& aq, AWSConnector& aws): bq(bq), aq(aq), aws(aws){};
         void checkAndPush();
         void checkAndPublish();
    private:
        ButtonQueue& bq;
        AWSQueue& aq;
        AWSConnector& aws;
};