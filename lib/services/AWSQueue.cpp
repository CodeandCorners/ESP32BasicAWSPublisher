#include "AWSQueue.h"
#include <optional>


std::optional<AWSEvent> AWSQueue::get(){
    if(queue.size() == 0) {
        return std::nullopt;
    } else {
        AWSEvent bp = queue.front();
        queue.erase(queue.begin());
        return bp;
    }
}
void AWSQueue::push(AWSEvent bp) {
    queue.push_back(bp);
}