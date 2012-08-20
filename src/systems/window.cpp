#include "systems/window.hpp"
#include "world.hpp"

// TODO:  Allow all this to be configured.
WindowSystem::WindowSystem(World& w)
    : System(w), window_(sf::VideoMode(800, 600), "Still no darn name") {
}

void WindowSystem::do_update(int) {
    sf::Event event;
    window_.pollEvent(event);
    if (event.type == sf::Event::Closed)
        window_.close();
}
