#pragma once

#include "system.hpp"
#include "typemap.hpp"
#include "component_list.hpp"
#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class Entity;

//! A single gameplay instance.
class World {
    // More specialised class for working with component lists.
    // Handy because we want to associate T with ComponentList<T>.
    class : boost::noncopyable {
        TypeMap map_;
      public:
        template<typename T>
        ComponentList<T>& get() {
            return map_.get<ComponentList<T>>();
        }
    } component_lists_;
 
    boost::ptr_vector<System> systems_;
    std::vector<std::shared_ptr<Entity>> entities_;
 
  public:
    //! Create a new entity in this world.
    Entity& new_entity();

    //! Construct a new subsystem with the given type.
    //!
    //! Arguments are forwarded to the constructor of T.
    template<typename T, typename... Args>
    void add_system(Args... args);
    
    //! Access a component list for a given type.
    template<typename T>
    ComponentList<T>& get_components();

    template<typename T>
    void register_component(std::weak_ptr<T>);

    //! Request that all systems update with the given timestep.
    void update(int deltat);
};

template<typename T, typename... Args>
void World::add_system(Args... args) {
    systems_.push_back(new T(*this, std::forward<Args>(args)...));
}

template<typename T>
void World::register_component(std::weak_ptr<T> comp) {
    get_components<T>().add_component(comp);
}

 
template<typename T>
ComponentList<T>& World::get_components() {
    return component_lists_.get<T>();
}
 
