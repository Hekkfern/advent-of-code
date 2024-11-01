#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "utils/Concepts.hpp"
#include <cstdint>
#include <cstdlib>

namespace utils::geometry3d {

/**
 * @brief      Describes a Line in 3D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Line3D {
public:
    /**
     * Number of vertexes of a Line.
     */
    static constexpr uint32_t NumberOfVertexes{2U};

    /**
     * @brief      Default constructor.
     */
    explicit Line3D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertex1  The first point.
     * @param[in]  vertex2  The second point.
     */
    explicit Line3D(Point3D<T> const& vertex1, Point3D<T> const& vertex2)
        : mVertexes{vertex1, vertex2}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coord1  The first point.
     * @param[in]  coord2  The second point.
     */
    explicit Line3D(
        Coordinate3D<T> const& coord1, Coordinate3D<T> const& coord2)
        : Line3D<T>{Point3D<T>{coord1}, Point3D<T>{coord2}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin  The origin
     * @param[in]  vector  The vector
     */
    explicit Line3D(Point3D<T> const& origin, Vector3D<T> const& vector)
        : Line3D<T>{origin, origin + vector}
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
    [[nodiscard]] std::array<Point3D<T>, NumberOfVertexes> getVertexes() const
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
    [[nodiscard]] bool operator==(Line3D<T> const& other) const
    {
        return mVertexes == other.mVertexes;
    }
    /**
     * @brief      Tells if the vector follows any special direction, like being
     *             horizontal, vertical, or diagonal.
     *
     * @return     Enum with the result.
     */
    [[nodiscard]] constexpr Line3DType is() const noexcept
    {
        if (isZero()) {
            return Line3DType::Zero;
        } else if (isHorizontal()) {
            return Line3DType::Horizontal;
        } else if (isVertical()) {
            return Line3DType::Vertical;
        } else if (isDiagonal()) {
            return Line3DType::Diagonal;
        } else {
            return Line3DType::Arbitrary;
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
    friend std::ostream& operator<<(std::ostream& os, Line3D<T> const& obj)
    {
        os << obj.mVertexes[0] << ", " << obj.mVertexes[1];
        return os;
    }
    /**
     * @brief      Determines if the line is empty, i.e., both coordinates are
     *             zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    [[nodiscard]] constexpr bool isZero() const noexcept
    {
        auto const thissize{this->size()};
        return thissize[0] == 0 && thissize[1] == 0;
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
     * @brief      Determines if it is a diagonal vector, i.e. its coordinate X
     *             is equal to its coordinate Y.
     *
     * @return     True if it is diagonal, False otherwise.
     */
    [[nodiscard]] bool isDiagonal() const
    {
        auto const thissize{this->size()};
        return std::abs(static_cast<std::intmax_t>(thissize[0]))
            == std::abs(static_cast<std::intmax_t>(thissize[1]));
    }

    /**
     * Stores the vertexes (points 3D) of this shape.
     */
    std::array<Point3D<T>, NumberOfVertexes> mVertexes{
        Point3D<T>{}, Point3D<T>{}};
};

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Line3D<T>> {
    std::size_t
    operator()(utils::geometry2d::Line3D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
