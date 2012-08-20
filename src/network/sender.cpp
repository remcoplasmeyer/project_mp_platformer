#include "network/sender.hpp"
#include "network/byte_sender.hpp"

Sender::Sender(std::unique_ptr<IByteSender>&& b_sender)
    : byte_sender_(std::move(b_sender)) {}
