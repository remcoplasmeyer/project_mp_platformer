#pragma once

#include "world.hpp"
#include <memory>
#include <vector>

class BaseComponent;

//! Represents any in-game object.
class Entity {
    World* world_;
    std::vector<std::shared_ptr<BaseComponent>> components_;
    
  public:
    //! Construct an entity residing in the given world.
    Entity(World&);

    //! Construct a component on this entity.
    //!
    //! Arguments are passed on to the constructor of the component.
    template<typename T, typename... Args>
    void add_component(Args&&... args);

    // TODO: Functions for querying components.
};
 
template<typename T, typename... Args>
void Entity::add_component(Args&&... args) {
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    components_.push_back(comp);
    world_->register_component(std::weak_ptr<T>(comp));
}
 
