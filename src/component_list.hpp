#pragma once

#include <boost/utility.hpp>
#include <vector>
#include <memory>

//! Class used for the world register components with.
template<typename T>
class ComponentList {
    typedef std::vector<T> ContainerType;
    ContainerType components_;

  public:
    typedef typename ContainerType::iterator Iterator;
    typedef typename ContainerType::const_iterator ConstIterator;

    //! Adds a component to the list.
    //!
    //! Note that adding components while iterating *will* invalidate iterators
    //! and if tha doesn't break anything, they probably *will* be iterated over
    //! unless you rely on that happening.
    //!
    //! Long story short, don't add components while iterating.
    void add_component(T);

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

    bool empty() const {
        return components_.empty();
    }
};

template<typename T>
void ComponentList<T>::add_component(T comp) {
    components_.push_back(comp);
}
 
