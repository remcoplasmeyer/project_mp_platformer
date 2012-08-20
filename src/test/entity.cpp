#include "components/base.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "system.hpp"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(add_component_without_awareness) {
    struct DummyComponent {};
    World world;
    auto e = world.new_entity();
    world.add_component_to<DummyComponent>(e);
    auto& comp = world.get_components<DummyComponent>();
    BOOST_ASSERT(comp.begin() != comp.end());
    auto p = comp.begin()->lock();
    BOOST_ASSERT(p);
}

BOOST_AUTO_TEST_CASE(add_component_with_entity_awareness) {
    struct AwareComponent : EntityTrackingComponent {};
    World world;
    auto e = world.new_entity();
    world.add_component_to<AwareComponent>(e);
    auto& comp = world.get_components<AwareComponent>();
    BOOST_ASSERT(comp.begin() != comp.end());
    auto p = comp.begin()->lock();
    BOOST_ASSERT(p);
    auto ep = p->get_entity().lock();
    BOOST_CHECK_EQUAL(ep, e);
}

