#include "components/physical.hpp"
#include "components/sprite.hpp"
#include "entity.hpp"

PhysicalComponent::PhysicalComponent()
    : velocity_(), inverse_mass_()
{
    try_link();
}

void PhysicalComponent::set_position(sf::Vector2f const& pos) {
    if (!sprite_)
        try_link();
    ASSERT(sprite_ && "Sorry, physical component without sprite not supported.");
    sprite_->set_position(pos);
}

void PhysicalComponent::add_to_position(sf::Vector2f const& diff) {
    if (!sprite_)
        try_link();
    ASSERT(sprite_ && "Sorry, physical component without sprite not supported.");
    sprite_->set_position(sprite_->get_position() + diff);
}

sf::Vector2f const& PhysicalComponent::get_position() const {
    if (!sprite_)
        try_link();
    ASSERT(sprite_ && "Sorry, physical component without sprite not supported.");
    return sprite_->get_position();
}

void PhysicalComponent::set_velocity(sf::Vector2f const& vec) {
    velocity_ = vec;
}

void PhysicalComponent::add_to_velocity(sf::Vector2f const& diff) {
    velocity_ += diff;
}

sf::Vector2f const& PhysicalComponent::get_velocity() const {
    return velocity_;
}

void PhysicalComponent::set_inverse_mass(float mass) {
    ASSERT(mass >= 0 && "Please don't add strange mass values without warning, mkay?");
    inverse_mass_ = mass;
}

float PhysicalComponent::get_inverse_mass() const {
    return inverse_mass_;
}

void PhysicalComponent::try_link() const {
    auto entity = get_entity().lock();
    if (!entity)
        return;
    sprite_ = entity->get_single<SpriteComponent>();
    
}
