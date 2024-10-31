#pragma once

#include "../Hash.hpp"
#include "Point3D.hpp"
#include "utils/Concepts.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <ostream>

namespace utils::geometry3d {

/**
 * @brief      Describes a Vector (i.e. a directional arrow) in 3D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Vector3D {
public:
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Vector3D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     * @param[in]  z     Coordinate Z.
     */
    constexpr explicit Vector3D(T x, T y, T z) noexcept
        : mX{x}
        , mY{y}
        , mZ{z}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin       The origin point.
     * @param[in]  destination  The destination point.
     */
    constexpr explicit Vector3D(
        Point3D<T> const& origin, Point3D<T> const& destination) noexcept
        : mX{destination.getX() - origin.getX()}
        , mY{destination.getY() - origin.getY()}
        , mZ{destination.getZ() - origin.getZ()}
    {
    }
    /**
     * @brief      Constructs a new instance where the the origin is the
     * coordinate (0,0,0) and the destination is the selected coordinate.
     *
     * @param[in]  coords     Coordinates.
     */
    constexpr explicit Vector3D(Coordinate3D<T> const coords) noexcept
        : Vector3D{coords.getX(), coords.getY(), coords.getZ()}
    {
    }
    /**
     * @brief      Constructs a new instance where the the origin is the
     *             coordinate (0,0,0) and the destination is the selected point.
     *
     * @param[in]  p     Point.
     */
    constexpr explicit Vector3D(Point3D<T> const p) noexcept
        : Vector3D{p.getX(), p.getY(), p.getZ()}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a group (X,Y,Z).
     */
    [[nodiscard]] constexpr Coordinate3D<T> getCoordinates() const noexcept
    {
        return Coordinate3D<T>{mX, mY, mZ};
    }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] constexpr T getX() const noexcept { return mX; }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] constexpr T getY() const noexcept { return mY; }
    /**
     * @brief      Gets the coordinate Z.
     *
     * @return     The coordinate Z.
     */
    [[nodiscard]] constexpr T getZ() const noexcept { return mZ; }
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Group of absolute coordinates (X,Y,Z).
     */
    [[nodiscard]] std::array<uint64_t, 3ULL> size() const noexcept
    {
        return {
            static_cast<uint64_t>(std::abs(mX)),
            static_cast<uint64_t>(std::abs(mY)),
            static_cast<uint64_t>(std::abs(mZ))};
    }
    /**
     * @brief      Gets the maximum, absolute coordinate between X, Y and Z.
     *
     * @return     The maximum, absolute coordinate value.
     */
    [[nodiscard]] constexpr uint64_t range() const noexcept
    {
        return std::max(
            std::max(
                static_cast<uint64_t>(std::abs(mX)),
                static_cast<uint64_t>(std::abs(mY))),
            static_cast<uint64_t>(std::abs(mZ)));
    }
    /**
     * @brief      Calculates the Manhattan Distance.
     *
     * @return     The Manhattan Distance value.
     *
     * @see        https://en.wikipedia.org/wiki/Taxicab_geometry
     */
    [[nodiscard]] constexpr uint64_t distance() const noexcept
    {
        return static_cast<uint64_t>(std::abs(mX))
            + static_cast<uint64_t>(std::abs(mY))
            + static_cast<uint64_t>(std::abs(mZ));
    }
    /**
     * @brief      Modifies the vector so the lengths becomes one (positive or
     * negative) up most, keeping the same direction.
     */
    [[nodiscard]] constexpr Vector3D normalize() const noexcept
    {
        Vector3D result{*this};
        // saturate X
        result.mX = std::clamp<T>(mX, -1, 1);
        // saturate Y
        result.mY = std::clamp<T>(mY, -1, 1);
        // saturate Z
        result.mZ = std::clamp<T>(mZ, -1, 1);
        return result;
    }
    /**
     * @brief      Determines if the vector is empty, i.e., all the coordinates
     * are zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    [[nodiscard]] bool isZero() const { return mX == 0 && mY == 0 && mZ == 0; }
    /**
     * @brief      Determines if it is an orthogonal vector, i.e. all its
     * coordinates but one are zero.
     *
     * @return     True if it is orthogonal, False otherwise.
     */
    [[nodiscard]] bool isOrthogonal() const
    {
        return (mX == 0 && mY == 0 && mZ != 0)
            || (mX == 0 && mY != 0 && mZ == 0)
            || (mX != 0 && mY == 0 && mZ == 0);
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(Vector3D const& other) const noexcept
        = default;
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] constexpr Vector3D
    operator+(Vector3D const& other) const noexcept
    {
        return Vector3D{mX + other.mX, mY + other.mY, mZ + other.mZ};
    }
    /**
     * @brief      Negation operator, which inverts the sign of both coordinates
     *             of the vector, i.e. inverts the direction of the vector.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Vector3D operator-() const noexcept
    {
        return Vector3D{-mX, -mY, -mZ};
    }
    /**
     * @brief      Subtraction operator, which subtracts the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Vector3D
    operator-(Vector3D const& other) const noexcept
    {
        return *this + -other;
    }
    /**
     * @brief      Factory method to create a new Vector based on the selected
     *             coordinates.
     *
     * @param[in]  x     The coordinate X.
     * @param[in]  y     The coordinate Y.
     *
     * @tparam     U     Type of the input coordinates.
     *
     * @return     New point.
     */
    template <std::integral U>
    [[nodiscard]] static Vector3D create(U x, U y, U z)
    {
        return Vector3D{
            static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)};
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
    {
        return "(" + std::to_string(mX) + "," + std::to_string(mY) + ","
            + std::to_string(mY) + ")";
    }
    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        std::size_t seed{27ULL};
        utils::hash::hash_combine(seed, mX);
        utils::hash::hash_combine(seed, mY);
        utils::hash::hash_combine(seed, mZ);
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
    operator<<(std::ostream& os, Vector3D<T> const& obj) noexcept
    {
        os << obj.toString();
        return os;
    }

    /**
     * Stores coordinate X.
     */
    T mX{0};
    /**
     * Stores coordinate Y.
     */
    T mY{0};
    /**
     * Stores coordinate Z.
     */
    T mZ{0};
};

/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  v  The vector to scale.
 * @param[in]  value     The scalar value to scale by.
 *
 * @tparam     T         Type of the coordinate values.
 * @tparam     U         Type of the scalar value.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T, IntegerType U>
[[nodiscard]] constexpr Vector3D<T>
operator*(Vector3D<T> const& v, U const value) noexcept
{
    return Vector3D<T>{
        static_cast<T>(value) * v.getX(),
        static_cast<T>(value) * v.getY(),
        static_cast<T>(value) * v.getZ()};
}
/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  value     The scalar value to scale by.
 * @param[in]  v  The vector to scale.
 *
 * @tparam     T         Type of the coordinate values.
 * @tparam     U         Type of the scalar value.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T, IntegerType U>
[[nodiscard]] constexpr Vector3D<T>
operator*(U const value, Vector3D<T> const& v) noexcept
{
    return v * value;
}

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Vector3D<T>> {
    std::size_t
    operator()(utils::geometry3d::Vector3D<T> const& k) const noexcept
    {
        return k.calculateHash();
    }
};
