#pragma once

#include "assert.hpp"

class Entity;

class BaseComponent {
  public:
    virtual ~BaseComponent() {}
};

class EntityTrackingComponent : public BaseComponent {
    Entity* entity_;
  public:
    void set_entity(Entity& entity) {
        ASSERT(!entity_ && "Attempted to set already-set entity.");
        entity_ = &entity;
    }

    Entity& get_entity() {
        ASSERT(entity_ && "Attempted to retrieve entity before it is set.");
        return *entity_;
    }
};
