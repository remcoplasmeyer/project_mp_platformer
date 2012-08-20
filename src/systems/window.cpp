#include "systems/window.hpp"
#include "world.hpp"

// TODO:  Allow all this to be configured.
WindowSystem::WindowSystem(World& w)
    : System(w), window_(sf::VideoMode(800, 600), "Still no darn name") {
}

void WindowSystem::do_update(int) {
    sf::Event event;
    // Temporary solution to make the game exit when the window is closed.
    if (!window_.isOpen())
        BOOST_THROW_EXCEPTION(BaseError());
    if (!window_.pollEvent(event))
        return;
    if (event.type == sf::Event::Closed)
        window_.close();
}
