#include "ButtonQueue.h"
#include "../models/ButtonPress.h"
#include <optional>
#include <sys/time.h>


std::vector<ButtonPress> ButtonQueue::getItemsGroupedByTime(){
    long nowMs = getNowMs();
    long rangeHighBufferMs = nowMs + timeMsBufferForEvents;
    long rangeLowBufferMs = nowMs - timeMsBufferForEvents;
    if (queue.empty() ) {
        return {};
    } else {
        ButtonPress firstElement = queue.front();
        int topElementTimeInMS = firstElement.epochNowMs;
        if(topElementTimeInMS < rangeHighBufferMs && topElementTimeInMS > rangeLowBufferMs) {
            return {};
        } else {
            long rangeHighBufferMsForTopEvent = topElementTimeInMS + timeMsBufferForEvents;
            long rangeLowBufferMsForTopEvent = topElementTimeInMS - timeMsBufferForEvents;

             auto splitIt = std::stable_partition(queue.begin(), queue.end(), 
        [rangeLowBufferMsForTopEvent, rangeHighBufferMsForTopEvent](const ButtonPress& bp) {
            return bp.epochNowMs >= rangeLowBufferMsForTopEvent && bp.epochNowMs <= rangeHighBufferMsForTopEvent;
        });


    std::vector<ButtonPress> similarItems(queue.begin(), splitIt);

    queue.erase(queue.begin(), splitIt);

    return similarItems;
        }
    }
}


long ButtonQueue::getNowMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    long ts = ((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    
    return ts;
}

void ButtonQueue::checkAndPush() {
    if (button1.isButtonPressed()) {
        long now = getNowMs();
        ButtonPress bp = ButtonPress{now, button1.getPinName()};
        Serial.println("PressService Pushed button press to queue");
        push(bp);
    }
};
void ButtonQueue::push(ButtonPress bp) {
    queue.push_back(bp);
}