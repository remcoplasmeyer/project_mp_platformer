#pragma once

#include "components/base.hpp"
#include <SFML/System/Vector2.hpp>
#include <boost/utility.hpp>

class SpriteComponent;

struct PhysicalComponent : EntityTrackingComponent, boost::noncopyable {
    PhysicalComponent();

    void set_position(sf::Vector2f const&);
    void add_to_position(sf::Vector2f const&);
    sf::Vector2f const& get_position() const;

    void set_velocity(sf::Vector2f const&);
    void add_to_velocity(sf::Vector2f const&);
    sf::Vector2f const& get_velocity() const;

    void set_inverse_mass(float);
    float get_inverse_mass() const;
    void try_link() const;
  private:
    mutable std::shared_ptr<SpriteComponent> sprite_;
    sf::Vector2f velocity_;
    float inverse_mass_;
};
