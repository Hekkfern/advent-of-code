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
            SECTION("Different name")
            {
                const auto vertex2{
                    Vertex<uint32_t, uint32_t>{"vertexAAAA", 12U}};
                CHECK_FALSE(vertex1 == vertex2);
                CHECK(vertex1 != vertex2);
            }
            SECTION("Different info")
            {
                const auto vertex2{Vertex<uint32_t, uint32_t>{"vertex", 222U}};
                CHECK(vertex1 == vertex2);
                CHECK_FALSE(vertex1 != vertex2);
            }
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

TEST_CASE("[Edge] Constructor", "[utils][graph][Edge]")
{
    SECTION("With integer-type information")
    {
        auto vertex{Vertex<uint32_t, uint32_t>{"vertex1", 24U}};
        auto edge{Edge<uint32_t, uint32_t>{vertex, 2U}};
        CHECK(edge.getWeight() == 2U);
        CHECK(edge.getDestinationVertex().getName() == "vertex1");
        CHECK(edge.getDestinationVertex().getInfo() == 24U);
    }
    SECTION("With custom-class-type information")
    {
        auto vertex{
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
        auto edge{Edge<CustomInfo, uint32_t>{vertex, 2U}};
        CHECK(edge.getWeight() == 2U);
        CHECK(edge.getDestinationVertex().getName() == "vertex1");
        CHECK(edge.getDestinationVertex().getInfo() == CustomInfo{12343U});
    }
}

TEST_CASE("[Edge] Equality operator", "[utils][graph][Edge]")
{
    SECTION("With integer-type information")
    {
        auto vertex{Vertex<uint32_t, uint32_t>{"vertex", 24U}};
        auto edge1{Edge<uint32_t, uint32_t>{vertex, 2U}};
        SECTION("Equal")
        {
            auto edge2{Edge<uint32_t, uint32_t>{vertex, 2U}};
            CHECK(edge1 == edge2);
            CHECK_FALSE(edge1 != edge2);
        }
        SECTION("Different")
        {
            SECTION("Different vertex")
            {
                auto vertex2{Vertex<uint32_t, uint32_t>{"vertex2", 45U}};
                auto edge2{Edge<uint32_t, uint32_t>{vertex2, 2U}};
                CHECK_FALSE(edge1 == edge2);
                CHECK(edge1 != edge2);
            }
            SECTION("Different weight")
            {
                auto vertex2{Vertex<uint32_t, uint32_t>{"vertex", 24U}};
                auto edge2{Edge<uint32_t, uint32_t>{vertex2, 15U}};
                CHECK_FALSE(edge1 == edge2);
                CHECK(edge1 != edge2);
            }
        }
    }
    SECTION("With custom-class-type information")
    {
        auto vertex{
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343U}}};
        auto edge1{Edge<CustomInfo, uint32_t>{vertex, 2U}};
        SECTION("Equal")
        {
            auto edge2{Edge<CustomInfo, uint32_t>{vertex, 2U}};
            CHECK(edge1 == edge2);
            CHECK_FALSE(edge1 != edge2);
        }
        SECTION("Different")
        {
            SECTION("Different vertex")
            {
                auto vertex2{
                    Vertex<CustomInfo, uint32_t>{"vertex2", CustomInfo{45U}}};
                auto edge2{Edge<CustomInfo, uint32_t>{vertex2, 2U}};
                CHECK_FALSE(edge1 == edge2);
                CHECK(edge1 != edge2);
            }
            SECTION("Different weight")
            {
                auto vertex2{
                    Vertex<CustomInfo, uint32_t>{"vertex", CustomInfo{24U}}};
                auto edge2{Edge<CustomInfo, uint32_t>{vertex2, 15U}};
                CHECK_FALSE(edge1 == edge2);
                CHECK(edge1 != edge2);
            }
        }
    }
}
