#pragma once

template<typename T>
class Receiver {
    T* subscriber_;
  public:
    Receiver(T& t) : subscriber_(t) {}
};

