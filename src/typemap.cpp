#include "typemap.hpp"

TypeMap::~TypeMap() {
    for (auto m : members_) {
        m->remove(this);
    }
}
