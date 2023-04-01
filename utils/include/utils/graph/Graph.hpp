#pragma once

#include "Edge.hpp"
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
template <typename T, typename W>
    requires(std::integral<W> || std::floating_point<W>)
    && std::equality_comparable<T>
class Graph {
public:
    bool addVertex(std::string&& name, T&& info)
    {
        if (containsVertex(name)) {
            return false;
        }
        mVertices.emplace(std::move(name), std::move(info));
        return true;
    }
    bool addEdge(
        const std::string& vertexName1,
        const std::string& vertexName2,
        const W weight)
    {
        if (!containsEdge(containsEdge(vertexName1, vertexName2))){
            return false;
        }
        // TODO
        return true;
    }
    size_t getNumberOfVertices() const { return mVertices.size(); }

private:
    Vertex<T, W>& getVertex(const std::string& vertexId)
    {
        return mVertices.at(vertexId);
    }
    bool containsVertex(std::string_view vertexId) const
    {
        return mVertices.contains(vertexId);
    }
    bool
    containsEdge(const std::string& vertexName1, const std::string& vertexName2)
    {
        if (!containsVertex(vertexName1) && !containsVertex(vertexName2)) {
            return false;
        }
        if (std::find_if(
                mVertices,
                [vertexName2](
                    const std::pair<std::string, Vertex<T, W>>& item) {
                    auto& edges{item.second.mEdges};
                    return std::find_if(
                               edges,
                               [vertexName2](const Edge<T, W>& edge) {
                                   return edge.getDestinationVertex().getId()
                                       == vertexName2;
                               })
                        != std::end(edges);
                })
            != std::end(mVertices)) {
            return true;
        }
        return false;
    }
    /**
     * List of vertices contained in this graph.
     */
    std::unordered_map<std::string, Vertex<T, W>> mVertices;
};

} // namespace utils::graph
