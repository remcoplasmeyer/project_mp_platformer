#include "network/local_message_queue.hpp"
#include <condition_variable>
#include <chrono>

void LocalMessageQueue::enqueue(Message const& message) {
    std::unique_lock<std::mutex> lock(mutex_);
    messages_.emplace(message);
}

Message LocalMessageQueue::dequeue() {
    std::condition_variable cond;
    Message m;
    std::unique_lock<std::mutex> lock(mutex_);
    cond.wait_for(lock, std::chrono::microseconds(1), [&](){ return !messages_.empty(); });
    m.swap(messages_.front());
    messages_.pop();
    return m;
}

