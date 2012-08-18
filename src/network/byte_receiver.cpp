#include "network/byte_receiver.hpp"

Message IByteReceiver::block_until_message() {
    return do_block_until_message();
}

IByteReceiver::~IByteReceiver() {}
