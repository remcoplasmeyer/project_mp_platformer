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
    class TypeMapStaticBase : boost::noncopyable {
        virtual void do_remove(TypeMap const*) = 0;
      protected:
        ~TypeMapStaticBase() = default;
      public:
        void remove(TypeMap const* p) {
            ASSERT(p);
            do_remove(p);
        }
    };

    template<typename T>
    class TypeMapStaticInstance : public TypeMapStaticBase {
        std::map<TypeMap const*, T> map_;
        
        void do_remove(TypeMap const* tm) {
            map_.erase(tm);
        }

      public:
        T& get(TypeMap const* tm) {
            // Should probably be rewritten to use emplace when GCC supports it.
            return map_[tm];
        }

        T const* cget(TypeMap const* tm) const {
            auto element = map_.find(tm);
            if (element != map_.end())
                return &element->second;
            return nullptr;
        }

    };

    template<typename T>
    class TypeMapDetail {
        TypeMapDetail() = delete;

      public:
        static TypeMapStaticInstance<T> map_;

        static T& get(TypeMap const* p) {
            return map_.get(p);
        }

        static T const* cget(TypeMap const* p) {
            return map_.cget(p);
        }
    };

    std::set<TypeMapStaticBase*> members_;
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
TypeMap::TypeMapStaticInstance<T> TypeMap::TypeMapDetail<T>::map_;
 
