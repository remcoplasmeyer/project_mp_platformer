#pragma once

#include "network/message.hpp"
#include <vector>

class IByteReceiver {
    virtual Message do_block_until_message() = 0;
  public:
    Message block_until_message();
    virtual ~IByteReceiver();
};

class ByteReceiver : public IByteReceiver {

};
