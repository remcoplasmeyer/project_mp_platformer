#pragma once

#include "system.hpp"
#include "typemap.hpp"
#include "components/base.hpp"
#include "component_list.hpp"
#include "component_to_list_map.hpp"
#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class Entity;

//! A single gameplay instance.
class World {
    ComponentToListMap<std::weak_ptr> component_lists_;
 
    boost::ptr_vector<ISystem> systems_;
    std::vector<std::shared_ptr<Entity>> entities_;

    //! Offer the component a weak_ptr to the entity.
    //!
    //! Components wishing to take advantage of this should publicly derive
    //! from EntityTrackingComponent.
    template<typename T>
    void register_entity_with_component(
            T& t,
            std::weak_ptr<Entity> e,
            typename std::enable_if<std::is_base_of<EntityTrackingComponent, T>::value>::type* = nullptr) {
        ASSERT(!e.expired() && "Attempting to add component to expired entity.");
        t.set_entity(e);
    }

    template<typename T>
    void register_entity_with_component(
            T&,
            std::weak_ptr<Entity>,
            typename std::enable_if<!std::is_base_of<EntityTrackingComponent, T>::value>::type* = nullptr) {
        // Do nothing, component does not wish to be registered with.
    }

    //! Add the component to the list of components of its type.
    template<typename T>
    void register_component(std::weak_ptr<T>);
 
  public:
    //! Create a new entity in this world.
    std::shared_ptr<Entity> new_entity();

    //! Construct a new subsystem with the given type.
    //!
    //! Arguments are forwarded to the constructor of T.
    template<typename T, typename... Args>
    void add_system(Args...);
    
    //! Access a component list for a given type.
    //!
    //! This does not allow one to add or remove components, but does allow
    //! their modification (very few systems need read-only access to
    //! components, and very few need to add or remove them).
    template<typename T>
    ComponentList<std::weak_ptr<T>> const* get_components() const;

    //! Add a component to an entity.
    template<typename T, typename... Args>
    void add_component_to(std::shared_ptr<Entity>, Args&&...);

    //! Request that all systems update with the given timestep.
    void update(int deltat);
};

#include "world_impl.hpp"
