#include "system.hpp"
#include "world.hpp"

System::System(World& w) : world_(&w) {}

void System::update(int deltat) {
    do_update(deltat);
}

World& System::get_world() {
    return *world_;
}

System::~System() {}
