#include "physics.hpp"
#include "components/physical.hpp"
#include "components/force.hpp"
#include "entity.hpp"
#include "world.hpp"
#include <numeric>

namespace {

void update_one_entity(PhysicalComponent& p, float deltat) {
    auto entity = p.get_entity().lock();
    if (!entity)
        return;
    auto forces = entity->get_components<ForceComponent>();
    if (!forces)
        return;
    auto total_force = std::accumulate(forces->begin(), forces->end(), sf::Vector2f(), 
            [&](sf::Vector2f lhs, decltype(*forces->begin()) rhs) {
                return lhs + rhs->force;
            });
    p.add_to_velocity(deltat * total_force * p.get_inverse_mass());
    p.add_to_position(deltat * p.get_velocity());
}

} // end anon namespace

PhysicsSystem::PhysicsSystem(World& world)
    : ISystem(world) {}

void PhysicsSystem::do_update(float deltat) {
    auto components = get_world().get_components<PhysicalComponent>();
    if (!components)
        return;
    for (auto& component : *components)
        if (auto p = component.lock())
            update_one_entity(*p, deltat);
}
