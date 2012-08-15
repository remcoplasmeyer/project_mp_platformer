#pragma once

#include "world.hpp"
#include <boost/utility.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <vector>
#include <memory>

//! Class used for the world register components with.
template<typename T>
class ComponentVector : boost::noncopyable {
    std::vector<T*> components_;
  public:
    typedef boost::indirect_iterator<typename std::vector<T*>::iterator> Iterator;
    typedef boost::indirect_iterator<typename std::vector<T*>::const_iterator> ConstIterator;

    //! Listen to the given world.
    ComponentVector(World&);

    //! Called by World to notify of a new component.
    void add_component(T*);

    Iterator begin() {
        return components_.begin();
    }

    ConstIterator begin() const {
        return components_.begin();
    }
 
    Iterator end() {
        return components_.end();
    }

    ConstIterator end() const {
        return components_.end();
    }
};

 
template<typename T>
ComponentVector<T>::ComponentVector(World& world) {
    world.request_registration(*this);
}
 
template<typename T>
void ComponentVector<T>::add_component(T* comp) {
    components_.push_back(comp);
}
 
