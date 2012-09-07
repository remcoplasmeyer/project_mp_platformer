#include "components/sprite.hpp"

SpriteComponent::SpriteComponent(sf::Texture const& texture)
    : sprite_(texture) {}

SpriteComponent::SpriteComponent(sf::Texture const& texture, sf::IntRect const& rectangle)
    : sprite_(texture, rectangle) {}

void SpriteComponent::set_position(float x, float y) {
    sprite_.setPosition(x, y);
}

void SpriteComponent::set_position(sf::Vector2f const& v) {
    sprite_.setPosition(v);
}

sf::Vector2f const& SpriteComponent::get_position() const {
    return sprite_.getPosition();
}

SpriteComponent::operator sf::Drawable const&() const {
    return sprite_;
}

