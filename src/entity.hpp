#pragma once

#include "world.hpp"
#include <boost/any.hpp>
#include <memory>
#include <vector>

//! Represents any in-game object.
class Entity {
    World* world_;
    std::vector<std::shared_ptr<boost::any>> components_;
    
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
    // Note: not thread safe.
    // On the other hand, push_backing to a vector isn't either.
    components_.emplace_back(std::forward<Args>(args)...);
    world_->register_component(components_.back());
}
 
