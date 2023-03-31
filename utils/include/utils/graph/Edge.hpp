#pragma once

namespace utils::graph {

template <class T>
class Vertex;
template <class T>
class Graph;

/**
 * @brief      It describes the link or path between two vertices.
 *
 * @tparam     T     { description }
 */
template <typename T>
class Edge {
public:
    Edge(const Vertex<T>& d, const double weight);
    friend class Graph<T>;
    friend class Vertex<T>;

private:
    Vertex<T>& dest;
    double mWeight;
    bool mVisited{false};
};

template <typename T>
Edge<T>::Edge(const Vertex<T>& d, const double weight)
    : dest(d)
    , mWeight(weight)
{
}

} // namespace utils::graph
