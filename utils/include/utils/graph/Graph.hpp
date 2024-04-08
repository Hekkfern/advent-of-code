#pragma once

#include "Vertex.hpp"
#include <range/v3/all.hpp>
#include <unordered_map>

namespace utils::graph {

/**
 * @brief      It describes the whole graph, with its nodes and connections
 *             between them.
 *
 * @tparam     T     Type of the information contained in the vertexes.
 * @tparam     W     Type of the weights value of the edges.
 */
template <std::equality_comparable T, UnsignedIntegerType W = uint32_t>
class Graph {
public:
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    bool addVertex(std::string const& name, T const& info)
    {
        auto [insertedItem, isInserted]{
            mVertices.emplace(name, Vertex<T, W>{name, info})};
        return isInserted;
    }
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    bool addVertex(std::string_view const name, T const& info)
    {
        auto [insertedItem, isInserted]{
            mVertices.emplace(name, Vertex<T, W>{name, info})};
        return isInserted;
    }
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    template <class U>
    requires std::convertible_to<U, T>
    bool addVertex(std::string&& name, U&& info)
    {
        std::string key{name};
        auto [insertedItem, isInserted]{mVertices.emplace(
            key, Vertex<T, W>{std::move(name), std::forward<U>(info)})};
        return isInserted;
    }
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  vertex  The vertex to add.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    bool addVertex(Vertex<T, W> const& vertex)
    {
        auto [insertedItem, isInserted]{mVertices.emplace(
            vertex.getName(),
            Vertex<T, W>{vertex.getName(), vertex.getInfo()})};
        return isInserted;
    }
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  vertex  The vertex to add.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    bool addVertex(Vertex<T, W>&& vertex)
    {
        auto [insertedItem, isInserted]{mVertices.emplace(std::move(vertex))};
        return isInserted;
    }
    /**
     * @brief      Removes a vertex.
     *
     * @param[in]  vertexName  The vertex name to remove.
     *
     * @return     True if the vertex was deleted. False, otherwise.
     */
    bool removeVertex(std::string const& vertexName)
    {
        // delete edges whose origin or destination is this vertex
        for (auto const& vertex : mVertices) {
            if (vertexName == vertex.first) {
                continue;
            }
            removeAllEdges(vertexName, vertex.first);
        }
        // delete vertex
        return mVertices.erase(vertexName) == 1U;
    }
    /**
     * @brief      Removes the vertices that match the provided condition.
     *
     * @param[in]  condition  The condition.
     */
    void
    removeVertexIf(std::function<bool(Vertex<T, W> const& vertex)> condition)
    {
        std::vector<std::string> erasableVertices{
            mVertices
            | ranges::views::filter([&condition](auto const& item) -> bool {
                  auto const& [key, value] = item;
                  return condition(value);
              })
            | ranges::views::transform([](auto const& item) {
                  auto const& [key, value] = item;
                  return key;
              })
            | ranges::to<std::vector>};
        // delete edges
        ranges::for_each(mVertices, [&erasableVertices](auto& item) {
            ranges::for_each(
                erasableVertices, [&item](std::string const& vertexName) {
                    item.second.removeEdge(vertexName);
                });
        });
        // delete vertices
        ranges::for_each(
            erasableVertices, [this](std::string const& vertexName) {
                mVertices.erase(vertexName);
            });
    }
    /**
     * @brief      Adds a directed (unidirectional) edge.
     *
     * @param[in]  vertexName1  The name of the origin vertex.
     * @param[in]  vertexName2  The name of the destination vertex.
     * @param[in]  weight       The path weight.
     *
     * @return     True if the edge was added. False, otherwise.
     */
    bool addDirectedEdge(
        std::string const& vertexName1,
        std::string const& vertexName2,
        W const weight)
    {
        // check that both vertices exist
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        // create the edge
        return mVertices.at(vertexName1)
            .addEdge(mVertices.at(vertexName2), weight);
    }
    /**
     * @brief      Adds a undirected (bidirectional) edge.
     *
     * @param[in]  vertexName1  The name of the origin vertex.
     * @param[in]  vertexName2  The name of the destination vertex.
     * @param[in]  weight       The path weight.
     *
     * @return     True if the edge was added. False, otherwise.
     */
    bool addUndirectedEdge(
        std::string const& vertexName1,
        std::string const& vertexName2,
        W const weight)
    {
        // check that both vertices exist
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        // create the edge
        return mVertices.at(vertexName1)
                   .addEdge(mVertices.at(vertexName2), weight)
            && mVertices.at(vertexName2)
                   .addEdge(mVertices.at(vertexName1), weight);
    }
    /**
     * @brief      Deletes a directed (unidirectional) edge.
     *
     * @param[in]  vertexName1  The name of the origin vertex.
     * @param[in]  vertexName2  The name of the destination vertex.
     *
     * @return     True if the edge was deleted. False, otherwise.
     */
    bool removeDirectedEdge(
        std::string const& vertexName1, std::string const& vertexName2)
    {
        // check that both vertices exist
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        // delete the edge
        return mVertices.at(vertexName1).removeEdge(vertexName2);
    }
    /**
     * @brief      Deletes all the edges whose origin and/or destination are the
     *             selected vertices.
     *
     * @param[in]  vertexName1  The name of one vertex.
     * @param[in]  vertexName2  The name of another vertex.
     *
     * @return     True if all the edges were deleted. False, otherwise.
     */
    bool removeAllEdges(
        std::string const& vertexName1, std::string const& vertexName2)
    {
        // check that both vertices exist
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
        // delete the edges
        mVertices.at(vertexName1).removeEdge(vertexName2);
        mVertices.at(vertexName2).removeEdge(vertexName1);
        return true;
    }
    /**
     * @brief      Gets the vertices.
     *
     * @return     List of vertices.
     */
    [[nodiscard]] std::unordered_map<std::string, Vertex<T, W>> const&
    getVertices() const
    {
        return mVertices;
    }
    /**
     * @brief      Gets the vertex whose name is the selected one.
     *
     * @param[in]  vertexName  The vertex name.
     *
     * @return     The vertex object.
     */
    [[nodiscard]] Vertex<T, W> const&
    getVertex(std::string const& vertexName) const
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
