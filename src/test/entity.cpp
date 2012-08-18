#include "components/base.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "system.hpp"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(add_component_without_awareness) {
    World world;
    auto& e = world.new_entity();
    e.add_component<BaseComponent>();
    auto& comp = world.get_components<BaseComponent>();
    BOOST_ASSERT(comp.begin() != comp.end());
    auto p = comp.begin()->lock();
    BOOST_ASSERT(p);
}

BOOST_AUTO_TEST_CASE(add_component_with_entity_awareness) {
    World world;
    auto& e = world.new_entity();
    e.add_component<EntityTrackingComponent>();
    auto& comp = world.get_components<EntityTrackingComponent>();
    BOOST_ASSERT(comp.begin() != comp.end());
    auto p = comp.begin()->lock();
    BOOST_ASSERT(p);
    BOOST_CHECK_EQUAL(&p->get_entity(), &e);
}

