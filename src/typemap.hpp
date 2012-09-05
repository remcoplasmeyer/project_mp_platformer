#pragma once

#include "assert.hpp"
#include <boost/utility.hpp>
#include <set>
#include <map>

//! A map of types to values.
//!
//! Associative container which allows mapping of types to values of that
//! type.
class TypeMap : boost::noncopyable {
    typedef void (*destruct_func)(void*);
    class TypeMapStaticInstance : boost::noncopyable {
        destruct_func destroy_;
        std::map<TypeMap*, void*> map_;

      public:
        TypeMapStaticInstance(destruct_func);
        void*& get(TypeMap* tm);
        void const* cget(TypeMap*) const;
        void remove(TypeMap*);
    };

    template<typename T>
    class TypeMapDetail {
        TypeMapDetail() = delete;

        static void destroy_impl(void* p) {
            delete static_cast<T*>(p);
        }

      public:
        static TypeMapStaticInstance map_;

        static T& get(TypeMap* p) {
            auto& element = map_.get(p);
            if (!element)
                element = new T();
            return *static_cast<T*>(element);
        }

        static T const* cget(TypeMap* p) {
            return static_cast<T const*>(map_.cget(p));
        }
    };

    std::set<TypeMapStaticInstance*> members_;
  public:
    //! Retrieve the data associated with the given type.
    template<typename T>
    T& get() {
        members_.insert(&TypeMapDetail<T>::map_);
        return TypeMapDetail<T>::get(this);
    }

    template<typename T>
    T const* cget() const {
        return TypeMapDetail<T>::cget(this);
    }

    ~TypeMap();
};
 
template<typename T>
TypeMap::TypeMapStaticInstance TypeMap::TypeMapDetail<T>::map_(TypeMap::TypeMapDetail<T>::destroy_impl);
 
