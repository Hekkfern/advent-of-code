#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Graph.hpp>

using namespace utils::graph;

class CustomInfo {
public:
    explicit CustomInfo(const uint32_t value)
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

TEST_CASE("[Graph] Constructor", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        const Graph<uint32_t, uint32_t> graph;
        CHECK(graph.getVertices().empty());
    }
    SECTION("With custom-class-type information")
    {
        const Graph<CustomInfo, uint32_t> graph;
        CHECK(graph.getVertices().empty());
    }
}

TEST_CASE("[Graph] addVertex() method", "[utils][graph][Graph]")
{
    SECTION("Vertex doesn't exist")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.addVertex("vertex1", 32U)};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.addVertex("vertex1", CustomInfo{32U})};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == CustomInfo{32U});
        }
    }
    SECTION("Vertex already exists")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.addVertex("vertex1", 32U)};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
            const bool result2{graph.addVertex("vertex1", 32U)};
            CHECK_FALSE(result2);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.addVertex("vertex1", CustomInfo{32U})};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == CustomInfo{32U});
            const bool result2{graph.addVertex("vertex1", CustomInfo{32U})};
            CHECK_FALSE(result2);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == CustomInfo{32U});
        }
    }
}

TEST_CASE("[Graph] removeVertex() method", "[utils][graph][Graph]")
{
    SECTION("Vertex exists")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            const bool result{graph.removeVertex("vertex1")};
            CHECK(result);
            CHECK(graph.getVertices().empty());
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            const bool result{graph.removeVertex("vertex1")};
            CHECK(result);
            CHECK(graph.getVertices().empty());
        }
    }
    SECTION("Vertex doesn't exist")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.removeVertex("vertex1")};
            CHECK_FALSE(result);
            CHECK(graph.getVertices().empty());
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo, uint32_t> graph;
            CHECK(graph.getVertices().empty());
            const bool result{graph.removeVertex("vertex1")};
            CHECK_FALSE(result);
            CHECK(graph.getVertices().empty());
        }
    }
}

TEST_CASE("[Graph] addDirectedEdge() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        SECTION("Success")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            graph.addVertex("vertex2", 11U);
            CHECK(graph.getVertices().size() == 2U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            const auto& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            const auto& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.empty());
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex2", 32U);
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
    SECTION("With custom-class-type information")
    {
        SECTION("Success")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            graph.addVertex("vertex2", CustomInfo{11U});
            CHECK(graph.getVertices().size() == 2U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            const auto& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            const auto& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.empty());
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex2", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
}

TEST_CASE("[Graph] addUndirectedEdge() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        SECTION("Success")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            graph.addVertex("vertex2", 11U);
            CHECK(graph.getVertices().size() == 2U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            const auto& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            const auto& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.size() == 1U);
            CHECK(vertex2Edges.at("vertex1").getWeight() == 3U);
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<uint32_t, uint32_t> graph;
            graph.addVertex("vertex2", 32U);
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
    SECTION("With custom-class-type information")
    {
        SECTION("Success")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            graph.addVertex("vertex2", CustomInfo{11U});
            CHECK(graph.getVertices().size() == 2U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            const auto& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            const auto& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.size() == 1U);
            CHECK(vertex2Edges.at("vertex1").getWeight() == 3U);
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<CustomInfo, uint32_t> graph;
            graph.addVertex("vertex2", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            auto result{graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
}