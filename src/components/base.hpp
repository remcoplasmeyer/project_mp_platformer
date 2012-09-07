#pragma once

#include "assert.hpp"
#include <memory>

class Entity;

class EntityTrackingComponent {
    std::weak_ptr<Entity> entity_;
  protected:
    ~EntityTrackingComponent() {}
  public:
    void set_entity(std::weak_ptr<Entity> entity) {
        ASSERT(entity_.expired() && "Attempted to set already-set entity.");
        entity_ = entity;
    }

    std::weak_ptr<Entity> get_entity() const {
        return entity_;
    }
};
