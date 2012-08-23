#include "systems/event.hpp"
#include "world.hpp"
#include "assert.hpp"
#include <map>

namespace {
    typedef void (*EventFunc)(World&, sf::Window&, sf::Event const&);

    void react_Closed(World&, sf::Window& window, sf::Event const&) {
        window.close();
    }

    // When we've got all events in here, we can switch to an array.
#define MAP_EVENTTYPE_TO_REACTION(name) {sf::Event::name, ::react_##name}
    std::map<sf::Event::EventType, EventFunc> const event_reactions {
        MAP_EVENTTYPE_TO_REACTION(Closed),
#undef MAP_EVENTTYPE_TO_REACTION
    };
}

EventSystem::EventSystem(World& world, sf::Window* window)
    : System(world), window_(window) {
}

void EventSystem::do_update(int) {
    ASSERT(window_->isOpen() && "Update on closed screen performed.");
    sf::Event event;
    if (!window_->pollEvent(event))
        return;
    auto reaction = event_reactions.find(event.type);
    if (reaction != event_reactions.end())
        (reaction->second)(get_world(), *window_, event);
}

