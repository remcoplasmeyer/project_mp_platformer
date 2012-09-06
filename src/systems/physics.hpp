#pragma once

#include "system.hpp"

class World;

class PhysicsSystem : public ISystem {
  public:
    PhysicsSystem(World&);
  private:
    void do_update(int);
};

