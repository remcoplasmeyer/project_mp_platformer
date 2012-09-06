#include "systems/event.hpp"
#include "world.hpp"
#include "components/player_controlled.hpp"
#include "components/sprite.hpp"
#include "assert.hpp"
#include <map>

namespace {

typedef void (*EventFunc)(World&, sf::Window&, sf::Event const&);

void react_Closed(World&, sf::Window& window, sf::Event const&) {
    window.close();
}

void react_MouseButtonPressed(World& w, sf::Window&, sf::Event const& e) {
    auto players = w.get_components<PlayerControlledComponent>();
    if (!players)
        return;
    for (auto& weak : *players) {
        auto player = weak.lock();
        if (!player)
            continue;
        auto entity = player->get_entity().lock();
        if (!entity)
            continue;
        auto sprite_p = entity->get_single<SpriteComponent>();
        ASSERT(sprite_p && "Player has no sprite!");
        auto& sprite = *sprite_p;
        sprite.setPosition(e.mouseButton.x, e.mouseButton.y);
    }
}

// When we've got all events in here, we can switch to an array.
#define MAP_EVENTTYPE_TO_REACTION(name) {sf::Event::name, ::react_##name}
std::map<sf::Event::EventType, EventFunc> const event_reactions {
    MAP_EVENTTYPE_TO_REACTION(Closed),
    MAP_EVENTTYPE_TO_REACTION(MouseButtonPressed),
#undef MAP_EVENTTYPE_TO_REACTION
};

} // -- end anon namespace

EventSystem::EventSystem(World& world, sf::Window* window)
    : ISystem(world), window_(window) {
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

