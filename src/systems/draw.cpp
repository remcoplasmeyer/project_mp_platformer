#include "systems/draw.hpp"
#include "components/sprite.hpp"
#include "world.hpp"

// TODO:  Allow all this to be configured.
DrawSystem::DrawSystem(World& world, sf::RenderWindow* window)
    : ISystem(world), window_(window) {
}

void DrawSystem::do_update(int) {
    window_->clear();
    auto& w = get_world();
    auto sprites = w.get_components<SpriteComponent>();
    if (!sprites)
        return;
    for (auto& weak : *sprites) {
        auto sprite = weak.lock();
        if (!sprite)
            continue;
        window_->draw(*sprite);
    }
    window_->display();
}
