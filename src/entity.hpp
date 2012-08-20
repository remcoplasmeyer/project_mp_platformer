#pragma once

#include "component_to_list_map.hpp"
#include <boost/utility.hpp>
#include <memory>
#include <vector>

class World;

// Hack to make sure only new_entity can create Entities.
class EntityCreationWorld {
    friend class World;
    EntityCreationWorld(World& world) : world_(&world) {}
  public:
    World* world_;
};

//! Represents any in-game object.
//!
//! Not copyable because we keep references to it that really
//! should not be invalidated.
class Entity : boost::noncopyable {
    World* world_;
    ComponentToListMap<std::shared_ptr> component_lists_;


  public:
    //! Construct an entity residing in the given world.
    Entity(EntityCreationWorld);

    //! Add a component to this entity.
    //!
    //! Arguments are passed on to the constructor of the component.
    template<typename T>
    void add_component(std::shared_ptr<T>);

    // TODO: Functions for querying components.
};

#include "world.hpp"
 
template<typename T>
void Entity::add_component(std::shared_ptr<T> comp) {
    ASSERT(comp && "Trying to add null component.");
    component_lists_.get<T>().add_component(comp);
    world_->register_component(std::weak_ptr<T>(comp));
}
 
