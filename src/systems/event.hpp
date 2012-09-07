#pragma once

#include "system.hpp"
#include <SFML/Window.hpp>

class World;

class EventSystem : public ISystem {
    sf::Window* window_;
  public:
    EventSystem(World&, sf::Window*);
  private:
    void do_update(float);
};
