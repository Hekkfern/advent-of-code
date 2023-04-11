#pragma once

#include "../Concepts.hpp"
#include <concepts>
#include <string>
#include <unordered_map>

namespace utils::graph {

template <std::equality_comparable T, UnsignedNumericType W>
class Edge;
template <std::equality_comparable T, UnsignedNumericType W>
class Vertex;

/**
 * @brief      It describes the link or path between two vertices.
 *
 * @tparam     T     Type of the information contained in the vertexes.
 * @tparam     W     Type of the weights value of the edges.
 */
template <std::equality_comparable T, UnsignedNumericType W>
class Edge {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param      destinationVertex  The destination vertex.
     * @param[in]  weight             The path weight.
     */
    Edge(Vertex<T, W>& destinationVertex, W weight)
        : mDestinationVertex{destinationVertex}
        , mWeight{weight}
    {
    }
    /**
     * @brief      Gets the weight.
     *
     * @return     The weight.
     */
    [[nodiscard]] W getWeight() const { return mWeight; }
    /**
     * @brief      Gets the destination vertex.
     *
     * @return     The destination vertex.
     */
    [[nodiscard]] Vertex<T, W>& getDestinationVertex() const { return mDestinationVertex; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(const Edge& other) const
    {
        return mDestinationVertex == other.mDestinationVertex
            && mWeight == other.mWeight;
    }

private:
    /**
     * Stores the destination vertex.
     */
    Vertex<T, W>& mDestinationVertex;
    /**
     * Stores the path weight.
     */
    W mWeight;
};

/**
 * @brief      It describes each node of the graph.
 *
 * @tparam     T     Type of the information contained in the vertexes.
 * @tparam     W     Type of the weights value of the edges.
 */
template <std::equality_comparable T, UnsignedNumericType W>
class Vertex {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     */
    explicit Vertex(std::string&& name, T&& info)
        : mName{std::forward<std::string>(name)}
        , mInfo{std::forward<T>(info)}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     */
    explicit Vertex(const std::string_view name, const T& info)
        : mName{name}
        , mInfo{info}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name  Unique identifier for this node.
     * @param[in]  info  Information to attach to this node.
     */
    explicit Vertex(const std::string& name, const T& info)
        : mName{name}
        , mInfo{info}
    {
    }
    /**
     * @brief      Gets the name of this node.
     *
     * @return     The name.
     */
    [[nodiscard]] const std::string& getName() const { return mName; }
    /**
     * @brief      Gets the information attached to this node.
     *
     * @return     The attached information.
     */
    [[nodiscard]] const T& getInfo() const { return mInfo; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(const Vertex& other) const { return mName == other.mName; }
    /**
     * @brief      Adds an edge between this vertex and another one.
     *
     * @param[in]  other   The other node to be connected to.
     * @param[in]  weight  Weight value of this path.
     *
     * @return     True if a new edge was added. False, otherwise.
     */
    bool addEdge(Vertex<T, W>& other, const W weight)
    {
        auto [insertedItem, isInserted]{
            mEdges.emplace(std::string{other.getName()}, Edge{other, weight})};
        return isInserted;
    }
    /**
     * @brief      Removes an edge between this vertex and another one.
     *
     * @param[in]  vertexName  The name of the vertex connected to.
     *
     * @return     True if the edge was deleted. False, otherwise.
     */
    bool removeEdge(const std::string& vertexName)
    {
        return mEdges.erase(vertexName) == 1U;
    }
    /**
     * @brief      Gets all the edges of this vertex.
     *
     * @return     List of edges.
     */
    [[nodiscard]] const std::unordered_map<std::string, Edge<T, W>>& getEdges() const
    {
        return mEdges;
    }

private:
    /**
     * Unique identifier.
     */
    std::string mName;
    /**
     * Information attached to this node.
     */
    T mInfo;
    /**
     * List of Adjacent Nodes, i.e. nodes which are connected to this one by an
     * edge.
     */
    std::unordered_map<std::string, Edge<T, W>> mEdges{};
};

} // namespace utils::graph

template <std::equality_comparable T, UnsignedNumericType W>
struct std::hash<utils::graph::Vertex<T, W>> {
    std::size_t operator()(const utils::graph::Vertex<T, W>& k) const noexcept
    {
        return std::hash<std::string>()(k.mName);
    }
};

template <std::equality_comparable T, UnsignedNumericType W>
struct std::hash<utils::graph::Edge<T, W>> {
    std::size_t operator()(const utils::graph::Edge<T, W>& k) const noexcept
    {
        return std::hash<std::string>()(k.getDestinationVertex().getName())
            ^ std::hash<W>()(k.getWeight());
    }
};
