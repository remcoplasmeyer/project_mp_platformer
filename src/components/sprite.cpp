#include "components/sprite.hpp"

SpriteComponent::SpriteComponent(sf::Texture const& texture)
    : sprite_(texture) {}

SpriteComponent::SpriteComponent(sf::Texture const& texture, sf::IntRect const& rectangle)
    : sprite_(texture, rectangle) {}

void SpriteComponent::setPosition(float x, float y) {
    sprite_.setPosition(x, y);
}

void SpriteComponent::setPosition(sf::Vector2f const& v) {
    sprite_.setPosition(v);
}

SpriteComponent::operator sf::Drawable const&() const {
    return sprite_;
}

