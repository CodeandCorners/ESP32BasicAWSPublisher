#include "ButtonQueue.h"
#include "../models/ButtonPress.h"
#include <optional>
#include <sys/time.h>


std::vector<ButtonPress> ButtonQueue::getItemsGroupedByTime(){
    uint64_t nowMs = getNowMs();
    uint64_t rangeHighBufferMs = nowMs + timeMsBufferForEvents;
    uint64_t rangeLowBufferMs = nowMs - timeMsBufferForEvents;
    if (queue.empty() ) {
        return {};
    } else {
        ButtonPress firstElement = queue.front();
        uint64_t topElementTimeInMS = firstElement.epochNowMs;
        if(topElementTimeInMS < rangeHighBufferMs && topElementTimeInMS > rangeLowBufferMs) {
            return {};
        } else {
            uint64_t rangeHighBufferMsForTopEvent = topElementTimeInMS + timeMsBufferForEvents;
            uint64_t rangeLowBufferMsForTopEvent = topElementTimeInMS - timeMsBufferForEvents;

             auto splitIt = std::stable_partition(queue.begin(), queue.end(), 
        [rangeLowBufferMsForTopEvent, rangeHighBufferMsForTopEvent](const ButtonPress& bp) {
            return bp.epochNowMs >= rangeLowBufferMsForTopEvent && bp.epochNowMs <= rangeHighBufferMsForTopEvent;
        });

    std::vector<ButtonPress> similarItems(queue.begin(), splitIt);

    queue.erase(queue.begin(), splitIt);
    Serial.println(similarItems.size());
    return similarItems;
        }
    }
}


uint64_t ButtonQueue::getNowMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    uint64_t ts = ((uint64_t)tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000);
    return ts;
}

void ButtonQueue::checkAndPush() {
    if (button1.isButtonPressed()) {
        uint64_t now = getNowMs();
        ButtonPress bp = ButtonPress{now, button1.getPinName()};
        Serial.println("PressService Pushed button press to queue");
        push(bp);
    }
};
void ButtonQueue::push(ButtonPress bp) {
    queue.push_back(bp);
}