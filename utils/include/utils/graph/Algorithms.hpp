#pragma once

#include "Graph.hpp"
#include <unordered_map>

namespace utils::graph {

/**
 * @brief      Applies Floyd-Warshall algorithm to calculate the shortest paths
 *             between all the vertexes.
 *
 * @param[in]  graph  The graph to apply the algorithm to.
 *
 * @tparam     T      Type of the information contained in the vertexes.
 * @tparam     W      Type of the weights value of the edges.
 *
 * @return     New graph.
 *
 * @see        https://en.wikipedia.org/wiki/Floyd-Warshall_algorithm
 */
template <std::equality_comparable T, UnsignedIntegerType W = uint32_t>
[[nodiscard]] Graph<T, W> applyFloydWarshall(const Graph<T, W>& graph)
{
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>>
        distances;
    // initialize all the paths with the known distance, or maximum distance
    for (auto& [fromName, fromVertex] : graph.getVertices()) {
        for (auto& [toName, toVertex] : graph.getVertices()) {
            if (fromName == toName) {
                distances[fromName][fromName] = 0U;
            } else if (fromVertex.getEdges().contains(toName)) {
                distances[fromName][toName]
                    = graph.getVertices()
                          .at(fromName)
                          .getEdges()
                          .at(toName)
                          .getWeight();
            } else {
                distances[fromName][toName] = std::numeric_limits<W>::max();
            }
        }
    }
    // paths that go via another node
    for (auto& [viaName, viaVertex] : graph.getVertices()) {
        for (auto& [fromName, fromVertex] : graph.getVertices()) {
            for (auto& [toName, toVertex] : graph.getVertices()) {
                const auto viaDistance{
                    distances[fromName][viaName] + distances[viaName][toName]};
                if (distances[fromName][toName] > viaDistance) {
                    distances[fromName][toName] = viaDistance;
                }
            }
        }
    }

    Graph<T, W> resultGraph;
    // copy vertexes
    for (const auto& [vertexName, vertexItem] : graph.getVertices()) {
        resultGraph.addVertex(vertexItem);
    }
    // add all paths
    for (const auto& [fromName, fromPaths] : distances) {
        for (auto [toName, weight] : fromPaths) {
            resultGraph.addDirectedEdge(
                fromName, toName, static_cast<W>(weight));
        }
    }

    return resultGraph;
}

} // namespace utils::graph
