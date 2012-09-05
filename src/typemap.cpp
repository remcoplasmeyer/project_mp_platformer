#include "typemap.hpp"


TypeMap::TypeMapStaticInstance::TypeMapStaticInstance(destruct_func f)
    : destroy_(f) {}

void*& TypeMap::TypeMapStaticInstance::get(TypeMap* tm) {
    return map_[tm];
}

void const* TypeMap::TypeMapStaticInstance::cget(TypeMap* tm) const {
    auto element = map_.find(tm);
    if (element != map_.end())
        return element->second;
    return nullptr;
}

void TypeMap::TypeMapStaticInstance::remove(TypeMap* tm) {
    auto element = map_.find(tm);
    destroy_(element->second);
    map_.erase(element);
}

TypeMap::~TypeMap() {
    for (auto m : members_) {
        m->remove(this);
    }
}
