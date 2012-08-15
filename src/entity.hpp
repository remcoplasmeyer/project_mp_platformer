#pragma once

#include "world.hpp"
#include <boost/any.hpp>
#include <memory>
#include <vector>

//! Represents any in-game object.
class Entity {
    World* world_;
    std::vector<boost::any> components_;
    
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
    components_.push_back(T(std::forward<Args>(args)...));
    world_->register_component(boost::any_cast<T>(&components_.back()));
}
 
