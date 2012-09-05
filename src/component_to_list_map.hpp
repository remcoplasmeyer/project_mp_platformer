#pragma once

#include "typemap.hpp"
#include "component_list.hpp"

//! More specialised class for working with component lists.
//!
//! Handy because we want to associate T with ComponentList<WrapType<T>>,
//! where WrapType is some smart pointer template.
template<template<class> class WrapType>
class ComponentToListMap : boost::noncopyable {
    TypeMap map_;
  public:
    //! Return the container associated with T.
    template<typename T>
    ComponentList<WrapType<T>>& get() {
        return map_.get<ComponentList<WrapType<T>>>();
    }

    template<typename T>
    ComponentList<WrapType<T>> const* cget() const {
        return map_.cget<ComponentList<WrapType<T>>>();
    }
};
