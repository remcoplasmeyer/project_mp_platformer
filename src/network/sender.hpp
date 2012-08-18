#pragma once

#include <memory>

class IByteSender;

class Sender {
    std::unique_ptr<IByteSender> byte_sender_;
  public:
    Sender(IByteSender*);
    template<typename T>
    void Send(T const& t);
};
