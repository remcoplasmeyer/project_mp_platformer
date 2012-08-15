#include "entity.hpp"
#include "world.hpp"
#include "component_vector.hpp"
#define BOOST_TEST_MODULE GeneralEntitySystem
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(make_empty_entity) {
    World world;
    Entity e(world);
}


BOOST_AUTO_TEST_CASE(ensure_component_is_registered) {
    struct TestComponent {
        TestComponent() : x(0) {}
        int x;
    };
    class TestSystem : public System {
        ComponentVector<TestComponent> vec_;
        void do_update(int) {
            // Can't use BOOST_CHECK_NE because the Iterator isn't printable.
            BOOST_ASSERT(vec_.begin() != vec_.end());
            auto it = vec_.begin();
            BOOST_CHECK_EQUAL(it->x, 0);
            it->x++;
            BOOST_CHECK_EQUAL(it->x, 1);
        }
      public:
        TestSystem(World& world) : vec_(world) {}
    };
    World world;
    world.add_system<TestSystem>();
    Entity e(world);
    e.add_component<TestComponent>();
    world.update(1);
}
