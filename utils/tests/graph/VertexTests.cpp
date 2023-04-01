#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Vertex.hpp>

using namespace utils::graph;

TEST_CASE(
    "[Vertex - constructor] Constructor for integer information",
    "[Vertex, Vertex_constructor]")
{
    const auto vertex{Vertex<uint32_t, uint32_t>{"vertex1", 24U}};
    CHECK(vertex.getName() == "vertex1");
    CHECK(vertex.getInfo() == 24U);
}

TEST_CASE(
    "[Vertex - constructor] Constructor for custom class information",
    "[Vertex, Vertex_constructor]")
{
    struct CustomInfo {
        uint32_t mValue;
        bool operator==(const CustomInfo& other) const
        {
            return mValue == other.mValue;
        }
    };
    const auto vertex{
        Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343}}};
    CHECK(vertex.getName() == "vertex1");
    CHECK(vertex.getInfo() == CustomInfo{12343});
}