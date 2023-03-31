#pragma once

#include <range/v3/all.hpp>
#include <vector>

namespace utils::graph {

template <class T>
class Edge;
template <class T>
class Graph;

/**
 * @brief      It describes each node of the graph.
 *
 * @tparam     T     Type of the attached information.
 */
template <typename T>
class Vertex {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  info    Information to attach to this node.
     */
    explicit Vertex(T&& info);
    /**
     * @brief      Gets the information attached to this node.
     *
     * @return     The attached information.
     */
    T& getInfo() const;
    int getNum() const;

private:
    friend class Graph<T>;
    /**
     * @brief         Adds an edge between this vertex and another one.
     *
     * @param[in,out] other  The other node to be connected to.
     * @param[in]     weight     Weight value of this path.
     */
    void addEdge(const Vertex<T>& other, double weight);
    /**
     * @brief      Removes an edge between this vertex and another one.
     *
     * @param      other     The other node connected to this one.
     *
     * @return     True if a connection was removed. False, otherwise.
     */
    bool removeEdgeTo(const Vertex<T>& other);
    /**
     * Information attached to this node.
     */
    T mInfo;
    /**
     * List of Adjacent Nodes, i.e. nodes which are connected to this one by an
     * edge.
     */
    std::vector<Edge<T>> mAdjacentNodes;
    /**
     * Internal variable used by graph algorithms
     */
    bool mVisited{false};

    int num{0};
    int low{0};
    Vertex<T>* path{nullptr};
};

template <typename T>
Vertex<T>::Vertex(T&& info)
    : mInfo(std::move(info))
{
}

template <typename T>
int Vertex<T>::getNum() const
{
    return num;
}

template <typename T>
T& Vertex<T>::getInfo() const
{
    return mInfo;
}

template <typename T>
bool Vertex<T>::removeEdgeTo(const Vertex<T>& other)
{
    auto it{ranges::find(mAdjacentNodes, other)};
    if (it != std::end(mAdjacentNodes)) {
        mAdjacentNodes.erase(it);
        return true;
    }
    return false;
}

template <typename T>
void Vertex<T>::addEdge(const Vertex<T>& other, const double weight)
{
    mAdjacentNodes.emplace_back(other, weight);
}

} // namespace utils::graph
