#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/graph/Graph.hpp>

using namespace utils::graph;

class CustomInfo {
public:
    explicit CustomInfo(uint32_t const value)
        : mValue{value}
    {
    }
    bool operator==(CustomInfo const& other) const
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
        Graph<uint32_t> const graph;
        CHECK(graph.getVertices().empty());
    }
    SECTION("With custom-class-type information")
    {
        Graph<CustomInfo> const graph;
        CHECK(graph.getVertices().empty());
    }
}

TEST_CASE("[Graph] addVertex() method", "[utils][graph][Graph]")
{
    SECTION("Vertex doesn't exist")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.addVertex("vertex1", 32U)};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.addVertex("vertex1", CustomInfo{32U})};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == CustomInfo{32U});
        }
    }
    SECTION("Vertex already exists")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.addVertex("vertex1", 32U)};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
            bool const result2{graph.addVertex("vertex1", 32U)};
            CHECK_FALSE(result2);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == 32U);
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.addVertex("vertex1", CustomInfo{32U})};
            CHECK(result);
            CHECK(graph.getVertices().size() == 1U);
            CHECK(graph.getVertex("vertex1").getInfo() == CustomInfo{32U});
            bool const result2{graph.addVertex("vertex1", CustomInfo{32U})};
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
            Graph<uint32_t> graph;
            CHECK(graph.getVertices().empty());
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.removeVertex("vertex1")};
            CHECK(result);
            CHECK(graph.getVertices().empty());
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo> graph;
            CHECK(graph.getVertices().empty());
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.removeVertex("vertex1")};
            CHECK(result);
            CHECK(graph.getVertices().empty());
        }
    }
    SECTION("Vertex doesn't exist")
    {
        SECTION("With integer-type information")
        {
            Graph<uint32_t> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.removeVertex("vertex1")};
            CHECK_FALSE(result);
            CHECK(graph.getVertices().empty());
        }
        SECTION("With custom-class-type information")
        {
            Graph<CustomInfo> graph;
            CHECK(graph.getVertices().empty());
            bool const result{graph.removeVertex("vertex1")};
            CHECK_FALSE(result);
            CHECK(graph.getVertices().empty());
        }
    }
}

TEST_CASE("[Graph] removeVertexIf() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        Graph<uint32_t> graph;
        CHECK(graph.getVertices().empty());
        graph.addVertex("vertex1", 32U);
        graph.addVertex("vertex2", 43U);
        graph.addVertex("vertex3", 43U);
        CHECK(graph.getVertices().size() == 3U);
        graph.addUndirectedEdge("vertex1", "vertex2", 1U);
        graph.addUndirectedEdge("vertex1", "vertex3", 2U);
        graph.removeVertexIf([](Vertex<uint32_t> const& vertex) -> bool {
            return vertex.getInfo() == 43U;
        });
        CHECK(graph.getVertices().size() == 1U);
        CHECK(graph.getVertices().at("vertex1").getEdges().empty());
    }
    SECTION("With custom-class-type information")
    {
        Graph<CustomInfo> graph;
        CHECK(graph.getVertices().empty());
        graph.addVertex("vertex1", CustomInfo{32U});
        graph.addVertex("vertex2", CustomInfo{43U});
        graph.addVertex("vertex3", CustomInfo{43U});
        CHECK(graph.getVertices().size() == 3U);
        graph.addUndirectedEdge("vertex1", "vertex2", 1U);
        graph.addUndirectedEdge("vertex1", "vertex3", 2U);
        graph.removeVertexIf([](Vertex<CustomInfo> const& vertex) -> bool {
            return vertex.getInfo() == CustomInfo{43U};
        });
        CHECK(graph.getVertices().size() == 1U);
        CHECK(graph.getVertices().at("vertex1").getEdges().empty());
    }
}

TEST_CASE("[Graph] addDirectedEdge() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        SECTION("Success")
        {
            Graph<uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            graph.addVertex("vertex2", 11U);
            CHECK(graph.getVertices().size() == 2U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            auto const& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            auto const& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.empty());
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<uint32_t> graph;
            graph.addVertex("vertex2", 32U);
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
    SECTION("With custom-class-type information")
    {
        SECTION("Success")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            graph.addVertex("vertex2", CustomInfo{11U});
            CHECK(graph.getVertices().size() == 2U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            auto const& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            auto const& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.empty());
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex2", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            bool const result{graph.addDirectedEdge("vertex1", "vertex2", 3U)};
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
            Graph<uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            graph.addVertex("vertex2", 11U);
            CHECK(graph.getVertices().size() == 2U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            auto const& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            auto const& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.size() == 1U);
            CHECK(vertex2Edges.at("vertex1").getWeight() == 3U);
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<uint32_t> graph;
            graph.addVertex("vertex1", 32U);
            CHECK(graph.getVertices().size() == 1U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<uint32_t> graph;
            graph.addVertex("vertex2", 32U);
            CHECK(graph.getVertices().size() == 1U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
    SECTION("With custom-class-type information")
    {
        SECTION("Success")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            graph.addVertex("vertex2", CustomInfo{11U});
            CHECK(graph.getVertices().size() == 2U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK(result);
            auto const& vertex1Edges{graph.getVertex("vertex1").getEdges()};
            CHECK(vertex1Edges.size() == 1U);
            CHECK(vertex1Edges.at("vertex2").getWeight() == 3U);
            auto const& vertex2Edges{graph.getVertex("vertex2").getEdges()};
            CHECK(vertex2Edges.size() == 1U);
            CHECK(vertex2Edges.at("vertex1").getWeight() == 3U);
        }
        SECTION("Vertex1 doesn't exist")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex1", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
        SECTION("Vertex2 doesn't exist")
        {
            Graph<CustomInfo> graph;
            graph.addVertex("vertex2", CustomInfo{32U});
            CHECK(graph.getVertices().size() == 1U);
            bool const result{
                graph.addUndirectedEdge("vertex1", "vertex2", 3U)};
            CHECK_FALSE(result);
        }
    }
}

TEST_CASE("[Graph] removeDirectedEdge() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        Graph<uint32_t> graph;
        graph.addVertex("vertex1", 32U);
        graph.addVertex("vertex2", 11U);
        SECTION("Edge is undirected")
        {
            graph.addUndirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().size() == 1U);
        }
        SECTION("Edge is directed")
        {
            graph.addDirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge doesn't exist")
        {
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK_FALSE(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
    }
    SECTION("With custom-class-type information")
    {
        Graph<CustomInfo> graph;
        graph.addVertex("vertex1", CustomInfo{32U});
        graph.addVertex("vertex2", CustomInfo{11U});
        SECTION("Edge is undirected")
        {
            graph.addUndirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().size() == 1U);
        }
        SECTION("Edge is directed")
        {
            graph.addDirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge doesn't exist")
        {
            bool const result{graph.removeDirectedEdge("vertex1", "vertex2")};
            CHECK_FALSE(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
    }
}

TEST_CASE("[Graph] removeAllEdges() method", "[utils][graph][Graph]")
{
    SECTION("With integer-type information")
    {
        Graph<uint32_t> graph;
        graph.addVertex("vertex1", 32U);
        graph.addVertex("vertex2", 11U);
        SECTION("Edge is undirected")
        {
            graph.addUndirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge is directed")
        {
            graph.addDirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge doesn't exist")
        {
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
    }
    SECTION("With custom-class-type information")
    {
        Graph<CustomInfo> graph;
        graph.addVertex("vertex1", CustomInfo{32U});
        graph.addVertex("vertex2", CustomInfo{11U});
        SECTION("Edge is undirected")
        {
            graph.addUndirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge is directed")
        {
            graph.addDirectedEdge("vertex1", "vertex2", 3U);
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
        SECTION("Edge doesn't exist")
        {
            bool const result{graph.removeAllEdges("vertex1", "vertex2")};
            CHECK(result);
            CHECK(graph.getVertex("vertex1").getEdges().empty());
            CHECK(graph.getVertex("vertex2").getEdges().empty());
        }
    }
}
