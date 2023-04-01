#pragma once

#include "../Concepts.hpp"
#include <concepts>
#include <string>
#include <string_view>
#include <vector>

namespace utils::graph {

template <std::equality_comparable T, NumericType W>
class Edge;
template <std::equality_comparable T, NumericType W>
class Vertex;

/**
 * @brief      It describes the link or path between two vertices.
 *
 * @tparam     T     Type of the attached information.
 * @tparam     W     Type of the weight value.
 */
template <std::equality_comparable T, NumericType W>
class Edge {
public:
    Edge(const Vertex<T, W>& destinationVertex, W weight)
        : mDestinationVertex(destinationVertex)
        , mWeight(weight)
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
template <std::equality_comparable T, NumericType W>
class Vertex {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  info    Information to attach to this node.
     * @param[in]  name    Unique identifier for this node.
     */
    Vertex(std::string&& name, T&& info)
        : mName{std::move(name)}
        , mInfo(std::move(info))
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
    bool operator==(const Vertex& other) const
    {
        return mName == other.mName;
    }
    /**
     * @brief         Adds an edge between this vertex and another one.
     *
     * @param[in,out] other  The other node to be connected to.
     * @param[in]     weight     Weight value of this path.
     */
    void addEdge(const Vertex& other, const W weight)
    {
        mEdges.emplace_back(other, weight);
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
    std::vector<Edge<T, W>> mEdges{};
};

} // namespace utils::graph

template <std::equality_comparable T, NumericType W>
struct std::hash<utils::graph::Vertex<T, W>> {
    std::size_t operator()(const utils::graph::Vertex<T, W>& k) const noexcept
    {
        return std::hash<std::string>()(k.mName);
    }
};
