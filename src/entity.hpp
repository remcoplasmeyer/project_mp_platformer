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

    //! Retrieve a single component of the given type.
    //!
    //! If no component of a given type exists, returns a default-constructed
    //! shared pointer.  If multiple exist, any may be returned.
    template<typename T>
    std::shared_ptr<T> get_single();

    //! Retrieve all components of a given type.
    template<typename T>
    ComponentList<std::shared_ptr<T>>& get_components();
};

#include "world.hpp"
 
template<typename T>
void Entity::add_component(std::shared_ptr<T> comp) {
    ASSERT(comp && "Trying to add null component.");
    component_lists_.get<T>().add_component(comp);
    world_->register_component(std::weak_ptr<T>(comp));
}
 
template<typename T>
std::shared_ptr<T> Entity::get_single() {
    auto& list = component_lists_.get<T>();
    if (list.empty())
        return std::shared_ptr<T>();
    return *list.begin();
}

template<typename T>
ComponentList<std::shared_ptr<T>>& Entity::get_components() {
    return component_lists_.get<T>();
}
