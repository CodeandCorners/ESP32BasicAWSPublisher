#include "ButtonQueue.h"
#include "../models/ButtonPress.h"
#include <optional>

std::optional<ButtonPress> ButtonQueue::get(){
    if(queue.size() == 0) {
        return std::nullopt;
    } else {
        ButtonPress bp = queue.front();
        queue.erase(queue.begin());
        return bp;
    }
}
void ButtonQueue:: push(ButtonPress bp) {
    queue.push_back(bp);
}