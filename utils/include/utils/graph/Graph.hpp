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
    bool addVertex(const std::string& name, const T& info)
    {
        auto [insertedItem, isInserted]{
            mVertices.emplace(name, Vertex<T, W>{name, info})};
        return isInserted;
    }
    bool addVertex(const std::string_view name, const T& info)
    {
        auto [insertedItem, isInserted]{
            mVertices.emplace(name, Vertex<T, W>{name, info})};
        return isInserted;
    }
    bool addVertex(std::string&& name, T&& info)
    {
        std::string key{name};
        auto [insertedItem, isInserted]{mVertices.emplace(
            key,
            Vertex<T, W>{
                std::forward<std::string>(name), std::forward<T>(info)})};
        return isInserted;
    }
    bool addVertex(const Vertex<T, W>& vertex)
    {
        auto [insertedItem, isInserted]{mVertices.emplace(
            vertex.getName(),
            Vertex<T, W>{vertex.getName(), vertex.getInfo()})};
        return isInserted;
    }
    bool removeVertex(const std::string& vertexName)
    {
        return mVertices.erase(vertexName) == 1U;
    }
    void
    removeVertexIf(std::function<bool(const Vertex<T, W>& vertex)> condition)
    {
        // TODO
        std::erase_if(mVertices, [&condition](const auto& item) -> bool {
            auto const& [key, value] = item;
            return condition(value);
        });
    }
    bool addDirectedEdge(
        const std::string& vertexName1,
        const std::string& vertexName2,
        const W weight)
    {
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        return mVertices.at(vertexName1)
            .addEdge(mVertices.at(vertexName2), weight);
    }
    bool addUndirectedEdge(
        const std::string& vertexName1,
        const std::string& vertexName2,
        const W weight)
    {
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        return mVertices.at(vertexName1)
                   .addEdge(mVertices.at(vertexName2), weight)
            && mVertices.at(vertexName2)
                   .addEdge(mVertices.at(vertexName1), weight);
    }
    bool removeDirectedEdge(
        const std::string& vertexName1, const std::string& vertexName2)
    {
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        return mVertices.at(vertexName1).removeEdge(vertexName2);
    }
    bool removeAllEdges(
        const std::string& vertexName1, const std::string& vertexName2)
    {
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        mVertices.at(vertexName1).removeEdge(vertexName2);
        mVertices.at(vertexName2).removeEdge(vertexName1);
        return true;
    }
    const std::unordered_map<std::string, Vertex<T, W>>& getVertices() const
    {
        return mVertices;
    }
    const Vertex<T, W>& getVertex(const std::string& vertexName) const
    {
        return mVertices.at(vertexName);
    }

private:
    /**
     * List of vertices contained in this graph.
     */
    std::unordered_map<std::string, Vertex<T, W>> mVertices{};
};

} // namespace utils::graph
