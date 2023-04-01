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

TEST_CASE("[Vertex] Constructor", "[Vertex, Vertex_constructor]")
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
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343}}};
        CHECK(vertex.getName() == "vertex1");
        CHECK(vertex.getInfo() == CustomInfo{12343});
    }
}

TEST_CASE("[Vertex] Equality operator", "[Vertex, Vertex_equality]")
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
            Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343}}};
        SECTION("Equal")
        {
            const auto vertex2{
                Vertex<CustomInfo, uint32_t>{"vertex1", CustomInfo{12343}}};
            CHECK(vertex1 == vertex2);
            CHECK_FALSE(vertex1 != vertex2);
        }
        SECTION("Different")
        {
            const auto vertex2{
                Vertex<CustomInfo, uint32_t>{"vertexAAAA", CustomInfo{54343}}};
            CHECK_FALSE(vertex1 == vertex2);
            CHECK(vertex1 != vertex2);
        }
    }
}
