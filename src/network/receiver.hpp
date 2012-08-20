#pragma once

class IByteReceiver;

template<typename T>
class Receiver {
    T* subscriber_;
    std::unique_ptr<IByteReceiver> b_receiver_;
  public:
    Receiver(T& t, std::unique_ptr<IByteReceiver>&& b_receiver)
        : subscriber_(&t), b_receiver_(std::move(b_receiver)) {}
};

