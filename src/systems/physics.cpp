#include "physics.hpp"
#include "components/physical.hpp"
#include "components/force.hpp"
#include "entity.hpp"
#include "world.hpp"
#include <numeric>

namespace {

void update_one_entity(PhysicalComponent& p) {
    auto entity = p.get_entity().lock();
    if (!entity)
        return;
    auto forces = entity->get_components<ForceComponent>();
    if (!forces)
        return;
    auto total_force = std::accumulate(forces->begin(), forces->end(), sf::Vector2<float>(), 
            [&](sf::Vector2<float> lhs, decltype(*forces->begin()) rhs) {
                return lhs + rhs->force;
            });
    p.velocity += total_force / p.mass;
    p.position += p.velocity;
}

} // end anon namespace

PhysicsSystem::PhysicsSystem(World& world)
    : ISystem(world) {}

void PhysicsSystem::do_update(int) {
    auto components = get_world().get_components<PhysicalComponent>();
    if (!components)
        return;
    for (auto& component : *components)
        if (auto p = component.lock())
            update_one_entity(*p);
}
