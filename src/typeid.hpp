#pragma once

// Own implementation of static type identity because the default one is
// non-copyable and thus storing it in ForceComponent doesn't work very well.

class TypeId {
    template<typename T>
    struct TypeIdImpl {
        static const TypeIdImpl id;
    };

    template<typename T>
    friend TypeId get_typeid();
    template<typename T>
    friend TypeId get_typeid(T const&);
    friend bool operator==(TypeId lhs, TypeId rhs);
    friend bool operator!=(TypeId lhs, TypeId rhs);

    void* id_;

    TypeId(void*);
  public:
    TypeId(TypeId const&) = default;
    TypeId();
};

bool operator==(TypeId lhs, TypeId rhs);
bool operator!=(TypeId lhs, TypeId rhs);

template<typename T>
TypeId get_typeid() {
    return TypeId(&TypeId::TypeIdImpl<T>::id);
}

template<typename T>
TypeId get_typeid(T const&) {
    return TypeId(&TypeId::TypeIdImpl<T>::id);
}

