#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Vertex.hpp>

using namespace utils::graph;

class CustomInfo {
public:
    CustomInfo(uint32_t value)
        : mValue{value}
    {
    }
    bool operator==(const CustomInfo& other) const
    {
        return mValue == other.mValue;
    }

private:
    uint32_t mValue;
};

TEST_CASE("[Vertex] Constructor", "[utils][graph][Vertex]")
{
    SECTION("With integer-type information")
    {
        const auto vertex{Vertex<uint32_t, uint32_t>{"vertex1", 24U}};
        CHECK(vertex.getName() == "vertex1");
        CHECK(vertex.getInfo() == 24U);
    }
    SECTION("With custom-class-type information")
    {
        const auto vertex{
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
        CHECK(vertex.getName() == "vertex1");
        CHECK(vertex.getInfo() == CustomInfo{12343U});
    }
}

TEST_CASE("[Vertex] Equality operator", "[utils][graph][Vertex]")
{
    SECTION("With integer-type information")
    {
        const auto vertex1{Vertex<uint32_t, uint32_t>{"vertex", 24U}};
        SECTION("Equal")
        {
            const auto vertex2{Vertex<uint32_t, uint32_t>{"vertex", 12U}};
            CHECK(vertex1 == vertex2);
            CHECK_FALSE(vertex1 != vertex2);
        }
        SECTION("Different")
        {
            const auto vertex2{Vertex<uint32_t, uint32_t>{"vertexAAAA", 12U}};
            CHECK_FALSE(vertex1 == vertex2);
            CHECK(vertex1 != vertex2);
        }
    }
    SECTION("With custom-class-type information")
    {
        const auto vertex1{
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
        SECTION("Equal")
        {
            const auto vertex2{
                Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
            CHECK(vertex1 == vertex2);
            CHECK_FALSE(vertex1 != vertex2);
        }
        SECTION("Different")
        {
            const auto vertex2{
                Vertex<CustomInfo, uint32_t>{"vertexAAAA", CustomInfo{54343U}}};
            CHECK_FALSE(vertex1 == vertex2);
            CHECK(vertex1 != vertex2);
        }
    }
}

TEST_CASE("[Vertex] addEdge method", "[utils][graph][Vertex]")
{
    SECTION("With integer-type information")
    {
        auto vertex1{Vertex<uint32_t, uint32_t>{"vertex1", 24U}};
        auto vertex2{Vertex<uint32_t, uint32_t>{"vertex2", 322U}};
        vertex1.addEdge(vertex2, 2U);
        CHECK(vertex1.getEdges().size() == 1U);
        CHECK(vertex1.getEdges()[0].getWeight() == 2U);
        auto& destinationVertex{vertex1.getEdges()[0].getDestinationVertex()};
        CHECK(destinationVertex.getName() == "vertex2");
        CHECK(destinationVertex.getInfo() == 322U);
    }
    SECTION("With custom-class-type information")
    {
        auto vertex1{
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
        auto vertex2{Vertex<CustomInfo, uint32_t>{"vertex2", CustomInfo{454U}}};
        vertex1.addEdge(vertex2, 2U);
        CHECK(vertex1.getEdges().size() == 1U);
        CHECK(vertex1.getEdges()[0].getWeight() == 2U);
        auto& destinationVertex{vertex1.getEdges()[0].getDestinationVertex()};
        CHECK(destinationVertex.getName() == "vertex2");
        CHECK(destinationVertex.getInfo() == 454U);
    }
}
