//
// Created by daily on 25-12-23.
//
#ifdef TEST_BUILD
#define CATCH_CONFIG_MAIN
#include <boost/graph/adjacency_list.hpp>
#include <boost/container/stable_vector.hpp>
#include <thread>
#include <vector>
#include <catch2/catch.hpp>

TEST_CASE("Boost Graph Test", "[boost_graph]") {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
    Graph g;

    add_edge(0, 1, g);
    add_edge(1, 2, g);
    add_edge(2, 3, g);
    add_edge(3, 0, g);

    REQUIRE(num_vertices(g) == 4);
    REQUIRE(num_edges(g) == 4);
}

TEST_CASE("Boost Stable Vector Basic Operations", "[stable_vector]") {
    boost::container::stable_vector<int> vec;

    // Fill the vector
    for(int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }

    // Test size and content
    REQUIRE(vec.size() == 5);
    for(size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == static_cast<int>(i));
    }

    // Iterator stability check
    auto it = vec.begin();
    REQUIRE(*it == 0);
    vec.push_back(5); // This should not invalidate 'it'
    REQUIRE(*it == 0);
}
#endif