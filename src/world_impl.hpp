#pragma once
#include "world.hpp"
#include "entity.hpp"
#include "components/base.hpp"

template<typename T, typename... Args>
void World::add_system(Args... args) {
    systems_.push_back(new T(*this, std::forward<Args>(args)...));
}

template<typename T>
void World::register_component(std::weak_ptr<T> comp) {
    ASSERT(!comp.expired() && "Attempting to register an expired component.");
    get_components<T>().add_component(comp);
}

template<typename T, typename... Args>
void World::add_component_to(std::shared_ptr<Entity> entity, Args&&... args) {
    ASSERT(entity && "Attempting to add component to expired entity.");
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    entity->add_component(comp);
    register_component<T>(std::weak_ptr<T>(comp));
    register_entity_with_component(*comp, std::weak_ptr<Entity>(entity));
}
 
template<typename T>
ComponentList<std::weak_ptr<T>>& World::get_components() {
    return component_lists_.get<T>();
}
 
