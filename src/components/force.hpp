#pragma once

#include "typeid.hpp"
#include <SFML/System/Vector2.hpp>

struct ForceComponent {
    sf::Vector2<float> force;
    TypeId owner;
};
