#pragma once

#include "system.hpp"
#include <SFML/Window.hpp>

class World;

class DrawSystem : public System {
    sf::Window* window_;
  public:
    DrawSystem(World&, sf::Window*);
  private:
    void do_update(int);
};
