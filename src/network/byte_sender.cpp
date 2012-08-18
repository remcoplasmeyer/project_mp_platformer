#include "network/byte_sender.hpp"

void IByteSender::send(Message const& message) {
    ASSERT(message.size() > 0 && "Do not want to send zero-length packet!");
    do_send(message);
}

IByteSender::~IByteSender() {}

void ByteSender::do_send(Message const&) {
    ASSERT(!"Not implemented yet.");
}
