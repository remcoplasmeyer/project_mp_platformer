#include "systems/draw.hpp"
#include "world.hpp"

// TODO:  Allow all this to be configured.
DrawSystem::DrawSystem(World& world, sf::Window* window)
    : System(world), window_(window) {
}

void DrawSystem::do_update(int) {
    // TODO:  Draw things.
}
