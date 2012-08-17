#pragma once

#include "components/base.hpp"
#include "world.hpp"
#include <boost/utility.hpp>
#include <memory>
#include <vector>

// Hack to make sure only new_entity can create Entities.
class EntityCreationWorld {
    friend Entity& World::new_entity();
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
    std::vector<std::shared_ptr<BaseComponent>> components_;

    template<typename T>
    void register_entity(T& t, typename std::enable_if<std::is_base_of<EntityTrackingComponent, T>::value>::type* = nullptr) {
        t.set_entity(*this);
    }

    template<typename T>
    void register_entity(T&, typename std::enable_if<!std::is_base_of<EntityTrackingComponent, T>::value>::type* = nullptr) {
        // Do nothing, component does not wish to be registered with.
    }
    
  public:
    //! Construct an entity residing in the given world.
    Entity(EntityCreationWorld);

    //! Add a component to this entity.
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
    register_entity(*comp);
    world_->register_component(std::weak_ptr<T>(comp));
}
 
