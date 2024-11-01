#pragma once

#include "Operations3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "utils/Concepts.hpp"
#include "utils/Hash.hpp"
#include <cstdint>
#include <cstdlib>

namespace utils::geometry3d {

/**
 * @brief Enum defining the different types of orthogonal lines.
 */
enum class OrthogonalLine3DType { Zero, Horizontal, Vertical };

/**
 * @brief      Describes a Line in 3D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class OrthogonalLine3D {
public:
    /**
     * Number of vertexes of a Line.
     */
    static constexpr uint32_t NumberOfVertexes{2U};

    /**
     * @brief      Default constructor.
     */
    explicit OrthogonalLine3D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertex1  The first point.
     * @param[in]  vertex2  The second point.
     */
    explicit OrthogonalLine3D(
        Point3D<T> const& vertex1, Point3D<T> const& vertex2)
        : mVertexes{vertex1, vertex2}
    {
        assert(
            is() == OrthogonalLine3DType::Zero
            || is() == OrthogonalLine3DType::Horizontal
            || is() == OrthogonalLine3DType::Vertical);
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coord1  The first point.
     * @param[in]  coord2  The second point.
     */
    explicit OrthogonalLine3D(
        Coordinate3D<T> const& coord1, Coordinate3D<T> const& coord2)
        : OrthogonalLine3D<T>{Point3D<T>{coord1}, Point3D<T>{coord2}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin  The origin
     * @param[in]  vector  The vector
     */
    explicit OrthogonalLine3D(
        Point3D<T> const& origin, Vector3D<T> const& vector)
        : OrthogonalLine3D<T>{origin, origin + vector}
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
    [[nodiscard]] bool operator==(OrthogonalLine3D<T> const& other) const
    {
        return mVertexes == other.mVertexes;
    }
    /**
     * @brief      Tells if the vector follows any special direction, like being
     *             horizontal, vertical, or diagonal.
     *
     * @return     Enum with the result.
     */
    [[nodiscard]] constexpr OrthogonalLine3DType is() const noexcept
    {
        if (isZero()) {
            return OrthogonalLine3DType::Zero;
        } else if (isHorizontal()) {
            return OrthogonalLine3DType::Horizontal;
        } else if (isVertical()) {
            return OrthogonalLine3DType::Vertical;
        } else {
            /* impossible */
            assert(false);
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
    /**
     * @brief      Gets the points that compose this line, included the
     *             vertexes.
     *
     * @note       The order of the points in the list is from the first vertex
     *             to the last.
     *
     * @return     List of points.
     */
    [[nodiscard]] std::vector<Point3D<T>> getPoints() const
    {
        /* get unary vector of movement */
        Vector3D<T> const vector{mVertexes[0], mVertexes[1]};
        auto const unaryVector{vector.normalize()};
        /* get points */
        std::vector<Point3D<T>> points{mVertexes[0]};
        Point3D point{mVertexes.front()};
        while (point != mVertexes[1]) {
            point += unaryVector;
            points.emplace_back(point);
        }
        return points;
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
    operator<<(std::ostream& os, OrthogonalLine3D<T> const& obj)
    {
        os << obj.mVertexes[0] << ", " << obj.mVertexes[1];
        return os;
    }
    /**
     * @brief      Determines if it is a empty line, i.e. its length is zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    [[nodiscard]] bool isZero() const
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
     * Stores the vertexes (points 3D) of this shape.
     */
    std::array<Point3D<T>, NumberOfVertexes> mVertexes{
        Point3D<T>{}, Point3D<T>{}};
};

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::OrthogonalLine3D<T>> {
    std::size_t
    operator()(utils::geometry2d::OrthogonalLine3D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
