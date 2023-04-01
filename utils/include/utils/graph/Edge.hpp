#pragma once

#include <concepts>

namespace utils::graph {

template <typename T, typename W>
class Vertex;

/**
 * @brief      It describes the link or path between two vertices.
 *
 * @tparam     T     Type of the attached information.
 * @tparam     W     Type of the weight value.
 */
template <typename T, typename W>
    requires(std::integral<W> || std::floating_point<W>)
    && std::equality_comparable<T>
class Edge {
public:
    Edge(const Vertex<T, W>& destinationVertex, W weight)
        : mDestinationVertex(destinationVertex)
        , mWeight(weight)
    {
    }
    W getWeight() const { return mWeight; }
    Vertex<W, T>& getDestinationVertex() const { return mDestinationVertex; }
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

} // namespace utils::graph
