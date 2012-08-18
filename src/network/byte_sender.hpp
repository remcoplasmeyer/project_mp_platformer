#pragma once

#include "network/message.hpp"
#include "assert.hpp"
#include <cstddef>

class IByteSender {
    virtual void do_send(Message const&) = 0;
  public:
    void send(Message const&);
    
    virtual ~IByteSender();
};

class ByteSender : public IByteSender {
    virtual void do_send(Message const&);
};

