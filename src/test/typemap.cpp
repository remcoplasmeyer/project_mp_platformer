#include "typemap.hpp"
#include <chrono>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(construct) {
    TypeMap m;
}

BOOST_AUTO_TEST_CASE(set_and_retrieve_single) {
    TypeMap m;
    m.get<int>() = 5;
    BOOST_CHECK_EQUAL(m.get<int>(), 5);
}

BOOST_AUTO_TEST_CASE(set_and_retrieve_multiple) {
    int const num_maps = 10;
    TypeMap maps[num_maps];
    for (int i = 0; i < num_maps; ++i)
        maps[i].get<int>() = i;
    for (int i = 0; i < num_maps; ++i)
        BOOST_CHECK_EQUAL(maps[i].get<int>(), i);
}

BOOST_AUTO_TEST_CASE(ensure_correct_destruction) {
    bool destructed = false;
    struct CheckDestruction {
        bool* d;
        ~CheckDestruction() { if (d) *d = true; }
    };
    {
        TypeMap m;
        m.get<CheckDestruction>().d = &destructed;
    }
    BOOST_CHECK(destructed);
}

BOOST_AUTO_TEST_CASE(ensure_reasonable_speed) {
    int const num_maps = 10000;
    TypeMap m[num_maps];
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < num_maps; ++i)
        m[i].get<int>() = i;
    auto end = std::chrono::steady_clock::now();
    BOOST_CHECK(end - begin < std::chrono::milliseconds(20));
}
