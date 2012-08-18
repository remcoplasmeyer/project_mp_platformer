#include "network/local_message_queue.hpp"

void LocalMessageQueue::enqueue(Message const& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    messages_.emplace(message);
    cv_.notify_one();
}

Message LocalMessageQueue::dequeue() {
    Message m;
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&](){ return !messages_.empty(); });
    m.swap(messages_.front());
    messages_.pop();
    return m;
}

