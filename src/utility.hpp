#pragma once

#include <memory>

// Taken from StackOverflow ( http://stackoverflow.com/q/7038357/559931 ):
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
