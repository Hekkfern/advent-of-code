#pragma once

#include "../Concepts.hpp"
#include <concepts>
#include <string>
#include <string_view>
#include <unordered_map>

namespace utils::graph {

template <std::equality_comparable T, UnsignedNumericType W>
class Edge;
template <std::equality_comparable T, UnsignedNumericType W>
class Vertex;

/**
 * @brief      It describes the link or path between two vertices.
 *
 * @tparam     T     Type of the attached information.
 * @tparam     W     Type of the weight value.
 */
template <std::equality_comparable T, UnsignedNumericType W>
class Edge {
public:
    Edge(Vertex<T, W>& destinationVertex, W weight)
        : mDestinationVertex{destinationVertex}
        , mWeight{weight}
    {
    }
    W getWeight() const { return mWeight; }
    Vertex<T, W>& getDestinationVertex() const { return mDestinationVertex; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Edge& other) const
    {
        return mDestinationVertex == other.mDestinationVertex
            && mWeight == other.mWeight;
    }

private:
    Vertex<T, W>& mDestinationVertex;
    W mWeight;
};

/**
 * @brief      It describes each node of the graph.
 *
 * @tparam     T     Type of the attached information.
 * @tparam     W     Type of the weight value.
 */
template <std::equality_comparable T, UnsignedNumericType W>
class Vertex {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  info    Information to attach to this node.
     * @param[in]  name    Unique identifier for this node.
     */
    Vertex(std::string&& name, T&& info)
        : mName{std::forward<std::string>(name)}
        , mInfo(std::forward<T>(info))
    {
    }
    std::string_view getName() const { return mName; }
    /**
     * @brief      Gets the information attached to this node.
     *
     * @return     The attached information.
     */
    const T& getInfo() const { return mInfo; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Vertex& other) const { return mName == other.mName; }
    /**
     * @brief         Adds an edge between this vertex and another one.
     *
     * @param[in] other  The other node to be connected to.
     * @param[in]     weight     Weight value of this path.
     *
     * @return True if a new edge was added. False, otherwise.
     */
    bool addEdge(Vertex<T, W>& other, const W weight)
    {
        auto [insertedItem, isInserted]{
            mEdges.emplace(std::string{other.getName()}, Edge{other, weight})};
        return isInserted;
    }
    std::unordered_map<std::string, Edge<T, W>>& getEdges() { return mEdges; }

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
