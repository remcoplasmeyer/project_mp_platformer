#pragma once

#include "world.hpp"
#include <boost/utility.hpp>
#include <vector>
#include <memory>

//! Class used for the world register components with.
template<typename T>
class ComponentVector : boost::noncopyable {
    typedef typename std::vector<std::shared_ptr<T>>::iterator Iterator;
    std::vector<std::shared_ptr<T>> components_;
  public:
    //! Listen to the given world.
    ComponentVector(World&);

    //! Called by World to notify of a new component.
    void add_component(std::shared_ptr<T>);

    // Temporary to allow for use in range-based for loops.
    // TODO: Make iterators refer to T, not std::shared_ptr<T>.
    Iterator begin() {
        return components_.begin();
    }
 
    Iterator end() {
        return components_.end();
    }

    // TODO: Access functions 
};

 
template<typename T>
ComponentVector<T>::ComponentVector(World& world) {
    world.request_registration(*this);
}
 
template<typename T>
void ComponentVector<T>::add_component(std::shared_ptr<T> comp) {
    components_.push_back(comp);
}
 
