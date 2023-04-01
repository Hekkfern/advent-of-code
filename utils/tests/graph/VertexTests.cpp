#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Vertex.hpp>

using namespace utils::graph;

TEST_CASE(
    "[Vertex - constructor] Constructor for integer information",
    "[Vertex, Vertex_constructor]")
{
    auto vertex{Vertex<uint32_t, uint32_t>{"vertex1", 24}};
    CHECK(vertex.getId() == "vertex1");
}