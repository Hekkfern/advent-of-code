#pragma once

#include "Graph.hpp"
#include <unordered_map>

namespace utils::graph {

template <std::equality_comparable T, UnsignedNumericType W>
Graph<T, W> applyFloydWarshall(const Graph<T, W>& graph)
{
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>>
        distances;
    // initialize all the paths with the known distance, or maximum distance
    for (auto& [fromName, fromVertex] : graph.mVertices) {
        for (auto& [toName, toVertex] : graph.mVertices) {
            if (fromName == toName) {
                distances[fromName][fromName] = 0U;
            } else if (fromVertex.getEdges().contains(toName)) {
                distances[fromName][toName]
                    = graph.mVertices.at(fromName)
                          .getEdges()
                          .at(toName)
                          .getWeight();
            } else {
                distances[fromName][toName] = std::numeric_limits<W>::max();
            }
        }
    }
    // paths that go via another node
    for (auto& [viaName, viaVertex] : graph.mVertices) {
        for (auto& [fromName, fromVertex] : graph.mVertices) {
            for (auto& [toName, toVertex] : graph.mVertices) {
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
    for (const auto& [vertexName, vertexItem] : graph.mVertices) {
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
