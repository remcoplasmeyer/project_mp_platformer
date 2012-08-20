#pragma once

#include "system.hpp"
#include <SFML/Window.hpp>

class World;

class WindowSystem : public System {
    sf::Window window_;
  public:
    WindowSystem(World&);
  private:
    void do_update(int);
};
