#pragma once

#include <range/v3/all.hpp>
#include <vector>

namespace utils::graph {

template <typename T, typename W>
class Vertex;
template <typename T, typename W>
class Edge;

/**
 * @brief      It describes the whole graph, with its nodes and connections
 *             between them.
 *
 * @tparam     T     { description }
 */
template <typename T, typename W>
    requires(std::integral<W> || std::floating_point<W>)
    && std::equality_comparable<T>
class Graph {
public:
    bool addVertex(std::string&& name, T&& info)
    {
        const bool notExist{
            ranges::find(mVertices, info) == ranges::end(mVertices)};
        if (notExist) {
            mVertices.emplace(std::move(name), std::move(info));
        }
        return notExist;
    }
    bool addEdge(
        const std::string& vertexName1,
        const std::string& vertexName2,
        const W weight)
    {
        // TODO
    }
    size_t getNumberOfVertices() const { return mVertices.size(); }

private:
    bool containsVertex(std::string_view vertexId) const
    {
        return ranges::find(mVertices, [vertexId](const Vertex<T, W>& vertex) {
            return vertex.getId() == vertexId;
        } != ranges::end(mVertices));
    }
    /**
     * List of vertices contained in this graph.
     */
    std::vector<Vertex<T, W>> mVertices;
};

} // namespace utils::graph
