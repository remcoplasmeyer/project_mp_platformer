#include "world.hpp"
#include "entity.hpp"

Entity& World::new_entity() {
    entities_.push_back(std::make_shared<Entity>(EntityCreationWorld(*this)));
    return *entities_.back();
}

void World::update(int deltat) {
    for (auto& system : systems_)
        system.update(deltat);
}

