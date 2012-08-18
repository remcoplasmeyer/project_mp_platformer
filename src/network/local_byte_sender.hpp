#pragma once

#include "network/byte_sender.hpp"
#include "network/local_message_queue.hpp"

class LocalByteSender : public IByteSender {
    LocalMessageQueue& msg_queue_;
    virtual void do_send(Message const&);
  public:
    LocalByteSender(LocalMessageQueue&);
};
