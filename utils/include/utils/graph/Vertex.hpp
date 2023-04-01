#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <vector>

namespace utils::graph {

template <typename T, typename W>
class Edge;

/**
 * @brief      It describes each node of the graph.
 *
 * @tparam     T     Type of the attached information.
 * @tparam     W     Type of the weight value.
 */
template <typename T, typename W>
    requires(std::integral<W> || std::floating_point<W>)
    && std::equality_comparable<T>
class Vertex {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  info    Information to attach to this node.
     * @param[in]  name    Unique identifier for this node.
     */
    Vertex(std::string&& name, T&& info)
        : mId{std::move(name)}
        , mInfo(std::move(info))
    {
    }
    std::string_view getId() const { return mId; }
    /**
     * @brief      Gets the information attached to this node.
     *
     * @return     The attached information.
     */
    T& getInfo() const { return mInfo; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Vertex& other) const
    {
        return mId == other.mId && mInfo == other.mInfo;
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
    std::string mId;
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

template <typename T, typename W>
struct std::hash<utils::graph::Vertex<T, W>> {
    std::size_t operator()(const utils::graph::Vertex<T, W>& k) const noexcept
    {
        return std::hash<std::string>()(k.mId);
    }
};
