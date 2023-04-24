#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Algorithms.hpp>

using namespace utils::graph;

TEST_CASE(
    "[Algorithms] applyFloydWarshall() function", "[utils][graph][Algorithms]")
{
    SECTION("Star graph")
    {
        SECTION("Undirected paths")
        {
            Graph<uint32_t> graph;
            graph.addVertex("AA", 1U);
            graph.addVertex("BB", 2U);
            graph.addVertex("CC", 3U);
            graph.addVertex("DD", 4U);
            graph.addUndirectedEdge("AA", "BB", 2U);
            graph.addUndirectedEdge("BB", "CC", 3U);
            graph.addUndirectedEdge("BB", "DD", 4U);
            auto const graph2{applyFloydWarshall<uint32_t>(graph)};
            CHECK(graph2.getVertices().size() == 4U);
            CHECK(graph2.getVertex("AA").getEdges().at("AA").getWeight() == 0U);
            CHECK(graph2.getVertex("AA").getEdges().at("BB").getWeight() == 2U);
            CHECK(graph2.getVertex("AA").getEdges().at("CC").getWeight() == 5U);
            CHECK(graph2.getVertex("AA").getEdges().at("DD").getWeight() == 6U);
            CHECK(graph2.getVertex("BB").getEdges().at("DD").getWeight() == 4U);
            CHECK(graph2.getVertex("DD").getEdges().at("AA").getWeight() == 6U);
            CHECK(graph2.getVertex("DD").getEdges().at("BB").getWeight() == 4U);
        }
        SECTION("Directed paths")
        {
            Graph<uint32_t> graph;
            graph.addVertex("AA", 1U);
            graph.addVertex("BB", 2U);
            graph.addVertex("CC", 3U);
            graph.addVertex("DD", 4U);
            graph.addDirectedEdge("AA", "BB", 2U);
            graph.addDirectedEdge("BB", "CC", 3U);
            graph.addDirectedEdge("BB", "DD", 4U);
            auto const graph2{applyFloydWarshall<uint32_t>(graph)};
            CHECK(graph2.getVertices().size() == 4U);
            CHECK(graph2.getVertex("AA").getEdges().at("AA").getWeight() == 0U);
            CHECK(graph2.getVertex("AA").getEdges().at("BB").getWeight() == 2U);
            CHECK(graph2.getVertex("AA").getEdges().at("CC").getWeight() == 5U);
            CHECK(graph2.getVertex("AA").getEdges().at("DD").getWeight() == 6U);
            CHECK(graph2.getVertex("BB").getEdges().at("DD").getWeight() == 4U);
            CHECK(
                graph2.getVertex("DD").getEdges().at("AA").getWeight()
                == std::numeric_limits<uint32_t>::max());
            CHECK(
                graph2.getVertex("DD").getEdges().at("BB").getWeight()
                == std::numeric_limits<uint32_t>::max());
        }
    }
    SECTION("Linear graph")
    {
        SECTION("Undirected paths")
        {
            Graph<uint32_t> graph;
            graph.addVertex("AA", 1U);
            graph.addVertex("BB", 2U);
            graph.addVertex("CC", 3U);
            graph.addVertex("DD", 4U);
            graph.addUndirectedEdge("AA", "BB", 2U);
            graph.addUndirectedEdge("BB", "CC", 3U);
            graph.addUndirectedEdge("CC", "DD", 4U);
            auto const graph2{applyFloydWarshall<uint32_t>(graph)};
            CHECK(graph2.getVertices().size() == 4U);
            CHECK(graph2.getVertex("AA").getEdges().at("AA").getWeight() == 0U);
            CHECK(graph2.getVertex("AA").getEdges().at("BB").getWeight() == 2U);
            CHECK(graph2.getVertex("AA").getEdges().at("CC").getWeight() == 5U);
            CHECK(graph2.getVertex("AA").getEdges().at("DD").getWeight() == 9U);
            CHECK(graph2.getVertex("BB").getEdges().at("DD").getWeight() == 7U);
            CHECK(graph2.getVertex("DD").getEdges().at("AA").getWeight() == 9U);
            CHECK(graph2.getVertex("DD").getEdges().at("BB").getWeight() == 7U);
        }
        SECTION("Directed paths")
        {
            Graph<uint32_t> graph;
            graph.addVertex("AA", 1U);
            graph.addVertex("BB", 2U);
            graph.addVertex("CC", 3U);
            graph.addVertex("DD", 4U);
            graph.addDirectedEdge("AA", "BB", 2U);
            graph.addDirectedEdge("BB", "CC", 3U);
            graph.addDirectedEdge("CC", "DD", 4U);
            auto const graph2{applyFloydWarshall<uint32_t>(graph)};
            CHECK(graph2.getVertices().size() == 4U);
            CHECK(graph2.getVertex("AA").getEdges().at("AA").getWeight() == 0U);
            CHECK(graph2.getVertex("AA").getEdges().at("BB").getWeight() == 2U);
            CHECK(graph2.getVertex("AA").getEdges().at("CC").getWeight() == 5U);
            CHECK(graph2.getVertex("AA").getEdges().at("DD").getWeight() == 9U);
            CHECK(graph2.getVertex("BB").getEdges().at("DD").getWeight() == 7U);
            CHECK(
                graph2.getVertex("DD").getEdges().at("AA").getWeight()
                == std::numeric_limits<uint32_t>::max());
            CHECK(
                graph2.getVertex("DD").getEdges().at("BB").getWeight()
                == std::numeric_limits<uint32_t>::max());
        }
    }
}
