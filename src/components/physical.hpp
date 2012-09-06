#pragma once

#include "components/base.hpp"
#include <SFML/System/Vector2.hpp>

struct PhysicalComponent : EntityTrackingComponent {
    sf::Vector2<float> position;
    sf::Vector2<float> velocity;
    float mass;
};
