#pragma once

#include "components/base.hpp"
#include "world.hpp"
#include <memory>
#include <vector>

//! Represents any in-game object.
class Entity {
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
    register_entity(*comp);
    world_->register_component(std::weak_ptr<T>(comp));
}
 
