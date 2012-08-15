#include "components/base.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "component_list.hpp"
#define BOOST_TEST_MODULE GeneralEntitySystem
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(make_empty_entity) {
    World world;
    Entity e(world);
}


BOOST_AUTO_TEST_CASE(ensure_component_is_registered) {
    struct TestComponent : BaseComponent {
        TestComponent() : x(0) {}
        int x;
    };
    class TestSystem : public System {
        World* world_;
        void do_update(int) {
            // Can't use BOOST_CHECK_NE because the Iterator isn't printable.
            auto& test_comps = world_->get_components<TestComponent>();
            BOOST_ASSERT(test_comps.begin() != test_comps.end());
            auto it = test_comps.begin();
            BOOST_ASSERT(!it->expired());
            auto p = it->lock();
            BOOST_ASSERT(p);
            BOOST_CHECK_EQUAL(p->x, 0);
            p->x++;
            BOOST_CHECK_EQUAL(p->x, 1);
        }
      public:
        TestSystem(World& world) : world_(&world) {}
    };
    World world;
    world.add_system<TestSystem>();
    Entity e(world);
    e.add_component<TestComponent>();
    world.update(1);
}

