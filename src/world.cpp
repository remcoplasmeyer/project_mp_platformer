#include "world.hpp"

void World::update(int deltat) {
    for (auto& system : systems_)
        system.update(deltat);
}

