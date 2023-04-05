#pragma once

#include "Graph.hpp"
#include <unordered_map>

namespace utils::graph {

// template <std::equality_comparable T, UnsignedNumericType W>
Graph<uint32_t, uint32_t>
applyFloydWarshall(const Graph<uint32_t, uint32_t>& graph)
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
                distances[fromName][toName] = std::numeric_limits<
                    uint32_t>::max();
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

    Graph<uint32_t, uint32_t> resultGraph;
    // copy vertexes

    // add other paths
    // TODO
    return resultGraph;
}

} // namespace utils::graph
