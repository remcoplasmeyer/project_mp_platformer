#include "system.hpp"
#include "world.hpp"

ISystem::ISystem(World& w) : world_(&w) {}

void ISystem::update(int deltat) {
    do_update(deltat);
}

World& ISystem::get_world() {
    return *world_;
}
