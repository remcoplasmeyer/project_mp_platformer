#pragma once

#include <boost/utility.hpp>
#include <map>

//! A map of types to values.
//!
//! Associative container which allows mapping of types to values of that
//! type.
class TypeMap : boost::noncopyable {
    template<typename T>
    class TypeMapDetail {
        static std::map<TypeMap*, T> map_;
      public:
        static T& get(TypeMap* p) {
            return map_[p];
        }
    };
  public:
    //! Retrieve the data associated with the given type.
    template<typename T>
    T& get() {
        return TypeMapDetail<T>::get(this);
    }
};
 
template<typename T>
std::map<TypeMap*, T> TypeMap::TypeMapDetail<T>::map_;
 
