#include "typeid.hpp"

TypeId::TypeId(void* id) : id_(id) {}
TypeId::TypeId() : id_() {}

bool operator==(TypeId lhs, TypeId rhs) {
    return lhs.id_ == rhs.id_;
}
bool operator!=(TypeId lhs, TypeId rhs) {
    return lhs.id_ != rhs.id_;
}
