#pragma once

#include "typemap.hpp"
#include "component_list.hpp"

//! More specialised class for working with component lists.
//!
//! Handy because we want to associate T with ComponentList<T>.
template<template<class> class WrapType>
class ComponentToListMap : boost::noncopyable {
    TypeMap map_;
  public:
    template<typename T>
    ComponentList<WrapType<T>>& get() {
        return map_.get<ComponentList<WrapType<T>>>();
    }
};
