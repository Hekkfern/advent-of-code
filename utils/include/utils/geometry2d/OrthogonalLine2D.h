#pragma once

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "utils/Concepts.hpp"
#include "utils/Hash.hpp"
#include <cstdint>
#include <cstdlib>

namespace utils::geometry2d {

/**
 * @brief Enum defining the different types of orthogonal lines.
 */
enum class OrthogonalLine2DType { Zero, Horizontal, Vertical };

/**
 * @brief      Describes a Line in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class OrthogonalLine2D {
public:
    /**
     * Number of vertexes of a Line.
     */
    static constexpr uint32_t NumberOfVertexes{2U};

    /**
     * @brief      Default constructor.
     */
    explicit OrthogonalLine2D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertex1  The first point.
     * @param[in]  vertex2  The second point.
     */
    explicit OrthogonalLine2D(
        Point2D<T> const& vertex1, Point2D<T> const& vertex2)
        : mVertexes{vertex1, vertex2}
    {
        assert(
            is() == OrthogonalLine2DType::Horizontal
            || is() == OrthogonalLine2DType::Vertical);
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coord1  The first point.
     * @param[in]  coord2  The second point.
     */
    explicit OrthogonalLine2D(
        Coordinate2D<T> const& coord1, Coordinate2D<T> const& coord2)
        : OrthogonalLine2D<T>{Point2D<T>{coord1}, Point2D<T>{coord2}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin  The origin
     * @param[in]  vector  The vector
     */
    explicit OrthogonalLine2D(
        Point2D<T> const& origin, Vector2D<T> const& vector)
        : OrthogonalLine2D<T>{origin, origin + vector}
    {
    }
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y).
     */
    [[nodiscard]] std::array<uint64_t, NumberOfVertexes> size() const
    {
        return {
            static_cast<uint64_t>(
                std::abs(mVertexes[0].getX() - mVertexes[1].getX())),
            static_cast<uint64_t>(
                std::abs(mVertexes[0].getY() - mVertexes[1].getY()))};
    }
    /**
     * @brief      Calculates the Manhattan Distance.
     *
     * @return     The Manhattan Distance value.
     *
     * @see        https://en.wikipedia.org/wiki/Taxicab_geometry
     */
    [[nodiscard]] uint64_t distance() const
    {
        return static_cast<uint64_t>(
                   std::abs(mVertexes[0].getX() - mVertexes[1].getX()))
            + static_cast<uint64_t>(std::abs(
                std::abs(mVertexes[0].getY() - mVertexes[1].getY())));
    }
    /**
     * @brief      Gets the vertexes.
     *
     * @return     List of vertexes.
     */
    [[nodiscard]] std::array<Point2D<T>, NumberOfVertexes> getVertexes() const
    {
        return mVertexes;
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(OrthogonalLine2D<T> const& other) const
    {
        return mVertexes == other.mVertexes;
    }
    /**
     * @brief      Tells if the vector follows any special direction, like being
     *             horizontal, vertical, or diagonal.
     *
     * @return     Enum with the result.
     */
    [[nodiscard]] constexpr OrthogonalLine2DType is() const noexcept
    {
        if (isHorizontal()) {
            return OrthogonalLine2DType::Horizontal;
        } else if (isVertical()) {
            return OrthogonalLine2DType::Vertical;
        } else {
            return OrthogonalLine2DType::Zero;
        }
    }
    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        std::size_t seed{0ULL};
        for (auto const& vertex : mVertexes) {
            utils::hash::hash_combine(seed, vertex);
        }
        return seed;
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os    The output stream.
     * @param[in]  obj   The object.
     *
     * @return     The updated output stream.
     */
    friend std::ostream&
    operator<<(std::ostream& os, OrthogonalLine2D<T> const& obj)
    {
        os << obj.mVertexes[0] << ", " << obj.mVertexes[1];
        return os;
    }
    /**
     * @brief      Determines if it is a horizontal vector, i.e. its coordinate
     *             Y is zero.
     *
     * @return     True if it is horizontal, False otherwise.
     */
    [[nodiscard]] bool isHorizontal() const
    {
        auto const thissize{this->size()};
        return thissize[1] == 0;
    }
    /**
     * @brief      Determines if it is a vertical vector, i.e. its coordinate X
     *             is zero.
     *
     * @return     True if it is vertical, False otherwise.
     */
    [[nodiscard]] bool isVertical() const
    {
        auto const thissize{this->size()};
        return thissize[0] == 0;
    }

    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::array<Point2D<T>, NumberOfVertexes> mVertexes{
        Point2D<T>{}, Point2D<T>{}};
};

} // namespace utils::geometry2d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::OrthogonalLine2D<T>> {
    std::size_t
    operator()(utils::geometry2d::OrthogonalLine2D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
