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
template <std::equality_comparable T, UnsignedIntegerType W>
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
    bool addVertex(const std::string& name, const T& info)
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
    bool addVertex(const std::string_view name, const T& info)
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
    bool addVertex(std::string&& name, T&& info)
    {
        std::string key{name};
        auto [insertedItem, isInserted]{mVertices.emplace(
            key,
            Vertex<T, W>{
                std::forward<std::string>(name), std::forward<T>(info)})};
        return isInserted;
    }
    /**
     * @brief      Adds a vertex.
     *
     * @param[in]  vertex  The vertex to add.
     *
     * @return     True if the vertex was added. False, otherwise.
     */
    bool addVertex(const Vertex<T, W>& vertex)
    {
        auto [insertedItem, isInserted]{mVertices.emplace(
            vertex.getName(),
            Vertex<T, W>{vertex.getName(), vertex.getInfo()})};
        return isInserted;
    }
    /**
     * @brief      Removes a vertex.
     *
     * @param[in]  vertexName  The vertex name to remove.
     *
     * @return     True if the vertex was deleted. False, otherwise.
     */
    bool removeVertex(const std::string& vertexName)
    {
        return mVertices.erase(vertexName) == 1U;
    }
    /**
     * @brief      Removes the vertices that match the provided condition.
     *
     * @param[in]  condition  The condition.
     */
    void
    removeVertexIf(std::function<bool(const Vertex<T, W>& vertex)> condition)
    {
        std::vector<std::string> erasableVertices{
            mVertices
            | ranges::views::filter([&condition](const auto& item) -> bool {
                  auto const& [key, value] = item;
                  return condition(value);
              })
            | ranges::views::transform([](const auto& item) {
                  auto const& [key, value] = item;
                  return key;
              })
            | ranges::to<std::vector>};
        // delete edges
        ranges::for_each(mVertices, [&erasableVertices](auto& item) {
            ranges::for_each(
                erasableVertices, [&item](const std::string& vertexName) {
                    item.second.removeEdge(vertexName);
                });
        });
        // delete vertices
        ranges::for_each(
            erasableVertices, [this](const std::string& vertexName) {
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
    /**
     * @brief      Deletes a directed (unidirectional) edge.
     *
     * @param[in]  vertexName1  The name of the origin vertex.
     * @param[in]  vertexName2  The name of the destination vertex.
     *
     * @return     True if the edge was deleted. False, otherwise.
     */
    bool removeDirectedEdge(
        const std::string& vertexName1, const std::string& vertexName2)
    {
        if (!mVertices.contains(vertexName1)
            || !mVertices.contains(vertexName2)) {
            return false;
        }
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
    /**
     * @brief      Gets the vertices.
     *
     * @return     List of vertices.
     */
    [[nodiscard]] const std::unordered_map<std::string, Vertex<T, W>>& getVertices() const
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
    [[nodiscard]] const Vertex<T, W>& getVertex(const std::string& vertexName) const
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
