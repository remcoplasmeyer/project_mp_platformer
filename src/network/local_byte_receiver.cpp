#include "network/local_byte_receiver.hpp"

Message LocalByteReceiver::do_block_until_message() {
    // Safe, as dequeue() blocks until there's data.
    return msg_queue_.dequeue();
}

LocalByteReceiver::LocalByteReceiver(LocalMessageQueue& lmq)
    : msg_queue_(lmq)
{}
