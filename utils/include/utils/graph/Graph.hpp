#pragma once

#include "Vertex.hpp"
#include <range/v3/all.hpp>
#include <unordered_map>

namespace utils::graph {

/**
 * @brief      It describes the whole graph, with its nodes and connections
 *             between them.
 *
 * @tparam     T     { description }
 */
template <std::equality_comparable T, UnsignedNumericType W>
class Graph {
public:
    bool addVertex(std::string&& name, T&& info)
    {
        std::string key{name};
        auto [insertedItem, isInserted]{mVertices.emplace(
            key,
            Vertex<T, W>{
                std::forward<std::string>(name), std::forward<T>(info)})};
        return isInserted;
    }
    bool addEdge(
        const std::string& vertexName1,
        const std::string& vertexName2,
        const W weight)
    {
        if (!mVertices.contains(vertexName1)
            && !mVertices.contains(vertexName2)) {
            return false;
        }
        return mVertices.at(vertexName1)
            .addEdge(mVertices.at(vertexName2), weight);
    }
    size_t getNumberOfVertices() const { return mVertices.size(); }
    Vertex<T, W>& getVertex(const std::string& vertexId)
    {
        return mVertices.at(vertexId);
    }

private:
    /**
     * List of vertices contained in this graph.
     */
    std::unordered_map<std::string, Vertex<T, W>> mVertices{};
};

} // namespace utils::graph
