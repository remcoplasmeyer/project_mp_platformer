#pragma once

#include "system.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class World;

class DrawSystem : public ISystem {
    sf::RenderWindow* window_;
  public:
    DrawSystem(World&, sf::RenderWindow*);
  private:
    void do_update(float);
};
