#pragma once

#include "assert.hpp"
#include <boost/utility.hpp>
#include <set>

//! A map of types to values.
//!
//! Associative container which allows mapping of types to values of that
//! type.
class TypeMap : boost::noncopyable {
    template<typename T>
    class TypeMapDetail {
        struct Node : boost::noncopyable {
            Node(void* key, Node* parent) : key(key), lhs(), rhs(), parent(parent), data() {}
            void* key;
            Node* lhs;
            Node* rhs;
            Node* parent;
            T data;
        };
        Node* root;
        
        typedef void (*destruct_func)(void*);
        static void destroy_impl(void* p) {
            delete static_cast<Node*>(p);
        }
        destruct_func destroy;

        // No member data past this point.

        Node*& get_parent_to_this(Node* current) {
            if (!current->parent)
                return root;
            if (current->parent->lhs == current)
                return current->parent->lhs;
            else
                return current->parent->rhs;
        }

        void remove_specific(Node* current) {
            Node*& parent_to_this = get_parent_to_this(current);
            if (!current->lhs && !current->rhs) {
                parent_to_this = nullptr;
                return;
            }
            if (!current->lhs) {
                parent_to_this = current->rhs;
                current->rhs->parent = current->parent;
                return;
            }
            if (!current->rhs) {
                parent_to_this = current->lhs;
                current->lhs->parent = current->parent;
                return;
            }
            Node* replacement = current->lhs;
            while (replacement->rhs)
                replacement = replacement->rhs;
            replacement->parent->rhs = replacement->lhs;
            replacement->lhs->parent = replacement->parent;

            parent_to_this = replacement;
            current->lhs->parent = replacement;
            current->rhs->parent = replacement;
            replacement->lhs = current->lhs;
            replacement->rhs = current->rhs;
            replacement->parent = current->parent;
        }

      public:
        static TypeMapDetail map_;

        TypeMapDetail() : destroy(destroy_impl), root() {}

        // Will construct if not found.
        Node* retrieve(void* key) {
            if (!root)
                return root = new Node(key, nullptr);
            Node* current = root;
            while (true) {
                if (key < current->key) {
                    if (current->lhs)
                        current = current->lhs;
                    else
                        return current->lhs = new Node(key, current);
                } else if (key > current->key) {
                    if (current->rhs)
                        current = current->rhs;
                    else
                        return current->rhs = new Node(key, current);
                } else {
                    return current;
                }
            }
            ASSERT(!"Unreachable code.");
        }

        static T& get(TypeMap* p) {
            return map_.retrieve(p)->data;
        }

        void remove(void* key) {
            Node* current = root;
            while (current) {
                if (key < current->key) {
                    current = current->lhs;
                } else if (key > current->key) {
                    current = current->rhs;
                } else {
                    remove_specific(current);
                    destroy(current);
                    return;
                }
            }
            ASSERT(!"Tried to remove a non-existent node.");
        }

        // Kept for debugging.
        void print(Node* p) const {
            if (!p)
                return;
            std::cerr << "(";
            print(p->lhs);
            std::cerr << " " << p->data << " ";
            print(p->rhs);
            std::cerr << ")";
        }

        void print() const {
            print(root);
            std::cerr << '\n';
        }
    };

    std::set<void*> members_;
  public:
    //! Retrieve the data associated with the given type.
    template<typename T>
    T& get() {
        members_.insert(&TypeMapDetail<T>::map_);
        return TypeMapDetail<T>::get(this);
    }

    ~TypeMap() {
        struct DummyForCleaningPurposes {};
        for (auto m : members_) {
            auto map = static_cast<TypeMapDetail<DummyForCleaningPurposes>*>(m);
            map->remove(this);
        }
    }

    template<typename T>
    static void print() {
        TypeMapDetail<T>::map_.print();
    }
};
 
template<typename T>
TypeMap::TypeMapDetail<T> TypeMap::TypeMapDetail<T>::map_;
 
