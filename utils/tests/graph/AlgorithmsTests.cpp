#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Algorithms.hpp>

using namespace utils::graph;

TEST_CASE(
    "[Algorithms] applyFloydWarshall() function", "[utils][graph][Algorithms]")
{
    Graph<uint32_t, uint32_t> graph;
    graph.addVertex("AA", 1U);
    graph.addVertex("BB", 2U);
    graph.addVertex("CC", 3U);
    graph.addVertex("DD", 4U);
    graph.addUndirectedEdge("AA", "BB", 1U);
    graph.addUndirectedEdge("BB", "CC", 1U);
    graph.addUndirectedEdge("BB", "DD", 1U);
    auto graph2{applyFloydWarshall(graph)};
    CHECK(graph2.getNumberOfVertices() == 4U);
}
