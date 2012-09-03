#pragma once

#include "components/base.hpp"
#include <SFML/Graphics/Sprite.hpp>

struct SpriteComponent : EntityTrackingComponent {
    // I do not want to expose the entire interface, due to possibility
    // of coordinate mis-match.  We should decide whether SpriteComponent
    // delegates to PositionComponent or the other way around.
  private:
    sf::Sprite sprite_;
  public:
    SpriteComponent(sf::Texture const&);
    SpriteComponent(sf::Texture const&, sf::IntRect const&);
    void setPosition(float, float);
    void setPosition(sf::Vector2f const&);
    operator sf::Drawable const&() const;
};
