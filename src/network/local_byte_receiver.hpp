#pragma once

#include "network/byte_receiver.hpp"
#include "network/local_message_queue.hpp"

class LocalByteReceiver : public IByteReceiver {
    LocalMessageQueue& msg_queue_;
    virtual Message do_block_until_message();
  public:
    LocalByteReceiver(LocalMessageQueue&);
};
