#pragma once

#include <boost/utility.hpp>
#include <vector>
#include <memory>

//! Class used for the world register components with.
template<typename T>
class ComponentList {
    typedef std::vector<std::weak_ptr<T>> ContainerType;
    ContainerType components_;

  public:
    typedef typename ContainerType::iterator Iterator;
    typedef typename ContainerType::const_iterator ConstIterator;

    //! Called by World to notify of a new component.
    void add_component(std::weak_ptr<T>);

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
void ComponentList<T>::add_component(std::weak_ptr<T> comp) {
    components_.push_back(comp);
}
 
