#include "network/local_byte_sender.hpp"

LocalByteSender::LocalByteSender(LocalMessageQueue& lmq)
    : msg_queue_(lmq)
{}

void LocalByteSender::do_send(Message const& msg) {
    msg_queue_.enqueue(msg);
}
