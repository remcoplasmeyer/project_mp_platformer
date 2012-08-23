#include "systems/event.hpp"
#include "world.hpp"
#include "assert.hpp"

EventSystem::EventSystem(World& world, sf::Window* window)
    : System(world), window_(window) {
}

void EventSystem::do_update(int) {
    ASSERT(window_->isOpen() && "Update on closed screen performed.");
    sf::Event event;
    if (!window_->pollEvent(event))
        return;
    if (event.type == sf::Event::Closed)
        window_->close();
}
