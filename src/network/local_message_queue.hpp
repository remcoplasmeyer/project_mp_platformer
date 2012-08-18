#pragma once

#include "network/message.hpp"
#include <queue>
#include <mutex>

//! Message queue for LocalByteSender and -Receiver.
class LocalMessageQueue {
    std::queue<Message> messages_;
    mutable std::mutex mutex_;

  public:
    //! Add an item to the end of the queue.
    void enqueue(Message const&);

    //! Retrieve the first item in the queue.
    //!
    //! If there is no such item, block until there is.
    Message dequeue();
};
