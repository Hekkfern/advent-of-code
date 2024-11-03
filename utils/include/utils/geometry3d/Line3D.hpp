#pragma once

#include "Operations3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cstdint>
#include <cstdlib>
#include <utils/Concepts.hpp>

namespace utils::geometry3d {

/**
 * @brief Enum defining the different types of lines.
 */
enum class Line3DType {
    Arbitrary,
    Zero,
    AcrossXAxis,
    AcrossYAxis,
    AcrossZAxis
};

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
    explicit Line3D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertex1  The first point.
     * @param[in]  vertex2  The second point.
     */
    explicit Line3D(
        Point3D<T> const& vertex1, Point3D<T> const& vertex2) noexcept
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
        Coordinate3D<T> const& coord1, Coordinate3D<T> const& coord2) noexcept
        : Line3D<T>{Point3D<T>{coord1}, Point3D<T>{coord2}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin  The origin
     * @param[in]  vector  The vector
     */
    explicit Line3D(
        Point3D<T> const& origin, Vector3D<T> const& vector) noexcept
        : Line3D<T>{origin, origin + vector}
    {
    }
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y,Z).
     */
    [[nodiscard]] std::array<uint64_t, 3U> size() const noexcept
    {
        return {
            static_cast<uint64_t>(
                std::abs(mVertexes[0].getX() - mVertexes[1].getX())),
            static_cast<uint64_t>(
                std::abs(mVertexes[0].getY() - mVertexes[1].getY())),
            static_cast<uint64_t>(
                std::abs(mVertexes[0].getZ() - mVertexes[1].getZ()))};
    }
    /**
     * @brief      Calculates the Manhattan Distance.
     *
     * @return     The Manhattan Distance value.
     *
     * @see        https://en.wikipedia.org/wiki/Taxicab_geometry
     */
    [[nodiscard]] uint64_t distance() const noexcept
    {
        return static_cast<uint64_t>(
                   std::abs(mVertexes[0].getX() - mVertexes[1].getX()))
            + static_cast<uint64_t>(std::abs(
                std::abs(mVertexes[0].getY() - mVertexes[1].getY())))
            + static_cast<uint64_t>(std::abs(
                mVertexes[0].getZ() - mVertexes[1].getZ()));
    }
    /**
     * @brief      Gets the vertexes.
     *
     * @return     List of vertexes.
     */
    [[nodiscard]] std::array<Point3D<T>, NumberOfVertexes>
    getVertexes() const noexcept
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
    [[nodiscard]] bool operator==(Line3D<T> const& other) const noexcept
        = default;
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
        } else if (isAcrossX()) {
            return Line3DType::AcrossXAxis;
        } else if (isAcrossY()) {
            return Line3DType::AcrossYAxis;
        } else if (isAcrossZ()) {
            return Line3DType::AcrossZAxis;
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
    /**
     * @brief Moves both vertexes as the provided vector indicates.
     *
     * @param[in] v Vector of movement of both vertexes.
     */
    void move(Vector3D<T> const& v) noexcept
    {
        for (auto& vertex : mVertexes) {
            vertex = utils::geometry3d::move(vertex, v);
        }
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
    operator<<(std::ostream& os, Line3D<T> const& obj) noexcept
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
        return thissize[0] == 0ULL && thissize[1] == 0ULL
            && thissize[2] == 0ULL;
    }
    /**
     * @brief      Determines if the line is drawn across X axis only, i.e. its
     * coordinate X is the only one changing between both vertexes.
     *
     * @return     True if the line moves across X axis, False otherwise.
     */
    [[nodiscard]] bool isAcrossX() const noexcept
    {
        auto const thissize{this->size()};
        return thissize[0] != 0ULL && thissize[1] == 0ULL
            && thissize[2] == 0ULL;
    }
    /**
     * @brief      Determines if the line is drawn across Y axis only, i.e. its
     * coordinate Y is the only one changing between both vertexes.
     *
     * @return     True if the line moves across X axis, False otherwise.
     */
    [[nodiscard]] bool isAcrossY() const noexcept
    {
        auto const thissize{this->size()};
        return thissize[0] == 0ULL && thissize[1] != 0ULL
            && thissize[2] == 0ULL;
    }
    /**
     * @brief      Determines if the line is drawn across Z axis only, i.e. its
     * coordinate Z is the only one changing between both vertexes.
     *
     * @return     True if the line moves across X axis, False otherwise.
     */
    [[nodiscard]] bool isAcrossZ() const noexcept
    {
        auto const thissize{this->size()};
        return thissize[0] == 0ULL && thissize[1] == 0ULL
            && thissize[2] != 0ULL;
    }

    /**
     * Stores the vertexes (points 3D) of this shape.
     */
    std::array<Point3D<T>, NumberOfVertexes> mVertexes{
        Point3D<T>{}, Point3D<T>{}};
};

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Line3D<T>> {
    std::size_t
    operator()(utils::geometry3d::Line3D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
