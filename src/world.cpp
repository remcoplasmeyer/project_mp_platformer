#include "world.hpp"
#include "entity.hpp"

std::shared_ptr<Entity> World::new_entity() {
    auto entity = std::make_shared<Entity>();
    entities_.push_back(entity);
    return entity;
}

void World::update(int deltat) {
    for (auto& system : systems_)
        system.update(deltat);
}

