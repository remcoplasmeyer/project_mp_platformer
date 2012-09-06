#include "components/base.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "component_list.hpp"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(make_empty_entity) {
    World world;
    world.new_entity();
}


BOOST_AUTO_TEST_CASE(ensure_component_is_registered) {
    struct TestComponent {
        TestComponent() : x(0) {}
        int x;
    };
    class TestSystem : public ISystem {
        void do_update(int) {
            (*num_updates_)++;
        }
      public:
        int* num_updates_;
        TestSystem(World& world, int* num_updates)
            : ISystem(world), num_updates_(num_updates) {}
    };
    World world;
    int num_updates = 0;
    world.add_system<TestSystem>(&num_updates);
    auto e = world.new_entity();
    world.add_component_to<TestComponent>(e);
    world.update(1);
    BOOST_CHECK_EQUAL(num_updates, 1);
    auto test_comps = world.get_components<TestComponent>();
    BOOST_ASSERT(test_comps);
    BOOST_ASSERT(test_comps->begin() != test_comps->end());
    auto it = test_comps->begin();
    BOOST_ASSERT(!it->expired());
    auto p = it->lock();
    BOOST_CHECK_EQUAL(p->x, 0);
    p->x++;
}

