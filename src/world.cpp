#include "world.hpp"
#include "entity.hpp"

Entity& World::new_entity() {
    entities_.emplace_back(EntityCreationWorld(*this));
    return entities_.back();
}

void World::update(int deltat) {
    for (auto& system : systems_)
        system.update(deltat);
}

