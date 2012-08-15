#pragma once

#include "system.hpp"
#include "typemap.hpp"
#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

template<typename T>
class ComponentVector;

//! A single gameplay instance.
class World {
    // More specialised class for working with vectors of component
    // vectors.
    class WorldTypeMap : boost::noncopyable {
        TypeMap map_;
      public:
        template<typename T>
        std::vector<ComponentVector<T>*>& get() {
            return map_.get<std::vector<ComponentVector<T>*>>();
        }
    } component_vectors_;
 
    boost::ptr_vector<System> systems_;
 
  public:
    //! Request that all new T components be registered with
    //! the given ComponentVector<T> instance.
    template<typename T>
    void request_registration(ComponentVector<T>&);

    //! Construct a new subsystem with the given type.
    //!
    //! Arguments are forwarded to the constructor of T.
    template<typename T, typename... Args>
    void add_system(Args... args);
    
    //! Register a newly-created component.
    template<typename T>
    void register_component(T*);

    //! Request that all systems update with the given timestep.
    void update(int deltat);
};

#include <iostream>

template<typename T>
void World::request_registration(ComponentVector<T>& ca) {
    component_vectors_.get<T>().push_back(&ca);
}
 
template<typename T, typename... Args>
void World::add_system(Args... args) {
    systems_.push_back(new T(*this, std::forward<Args>(args)...));
}
 
template<typename T>
void World::register_component(T* comp) {
    for (auto vector : component_vectors_.get<T>()) {
        vector->add_component(comp);
    }
}
 
