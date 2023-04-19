#pragma once

#include "../Concepts.hpp"
#include "Point3D.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <ostream>

namespace utils::geometry3d {

template <SignedIntegerType T = int32_t>
class Vector3D {
public:
    /**
     * @brief      Default constructor.
     */
    explicit Vector3D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     * @param[in]  z     Coordinate Z.
     */
    explicit Vector3D(T x, T y, T z)
        : mX{x}
        , mY{y}
        , mZ{z}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords     Coordinates.
     */
    explicit Vector3D(const Coord3D<T> coords)
        : mX{coords.mX}
        , mY{coords.mY}
        , mZ{coords.mZ}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin       The origin point.
     * @param[in]  destination  The destination point.
     */
    explicit Vector3D(const Point3D<T>& origin, const Point3D<T>& destination)
        : mX{destination.getX() - origin.getX()}
        , mY{destination.getY() - origin.getY()}
        , mZ{destination.getZ() - origin.getZ()}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a group (X,Y,Z).
     */
    [[nodiscard]] Coord3D<T> getCoordinates() const { return {mX, mY, mZ}; }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] T getX() const { return mX; }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] T getY() const { return mY; }
    /**
     * @brief      Gets the coordinate Z.
     *
     * @return     The coordinate Z.
     */
    [[nodiscard]] T getZ() const { return mZ; }
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Group of absolute coordinates (X,Y,Z).
     */
    [[nodiscard]] std::array<uint64_t, 3U> size() const
    {
        return {
            static_cast<uint64_t>(std::abs(mX)),
            static_cast<uint64_t>(std::abs(mY)),
            static_cast<uint64_t>(std::abs(mZ))};
    }
    /**
     * @brief      { function_description }
     *
     * @return     { description_of_the_return_value }
     */
    [[nodiscard]] uint64_t range() const
    {
        return std::max(std::max(std::abs(mX), std::abs(mY)), std::abs(mZ));
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
        return std::abs(mX) + std::abs(mY) + std::abs(mZ);
    }
    /**
     * @brief      Modifies the vector so the lengths becomes one (positive or
     * negative) up most, keeping the same direction.
     */
    void normalize()
    {
        // saturate X
        mX = std::clamp(mX, -1, 1);
        // saturate Y
        mY = std::clamp(mY, -1, 1);
        // saturate Z
        mY = std::clamp(mZ, -1, 1);
    }
    /**
     * @brief      Creates a normalized vector from this one.
     *
     * @return     The normalized vector.
     */
    [[nodiscard]] Vector3D getNormalized() const
    {
        Vector3D vector3D(*this);
        vector3D.normalize();
        return vector3D;
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
    [[nodiscard]] bool operator==(const Vector3D& other) const
    {
        return mX == other.mX && mY == other.mY && mZ == other.mZ;
    }
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] Vector3D operator+(const Vector3D& other) const
    {
        return Vector3D{mX + other.mX, mY + other.mY, mZ + other.mZ};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Vector3D operator-() const { return Vector3D{-mX, -mY, -mZ}; }
    /**
     * @brief      Subtraction operator.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Vector3D operator-(const Vector3D& other) const
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

private:
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& point2d)
    {
        os << '(' << point2d.mX << ',' << point2d.mY << ',' << point2d.mZ
           << ')';
        return os;
    }

    /**
     * Stores coordinate X.
     */
    int32_t mX{0U};
    /**
     * Stores coordinate Y.
     */
    int32_t mY{0U};
    /**
     * Stores coordinate Z.
     */
    int32_t mZ{0U};
};

/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  vector3d  The vector to scale.
 * @param[in]  value     The scalar value to scale by.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T>
Vector3D<T> operator*(const Vector3D<T>& vector3d, const int32_t value)
{
    return Vector3D{
        value * vector3d.getX(),
        value * vector3d.getY(),
        value * vector3d.getZ()};
}
/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  value     The scalar value to scale by.
 * @param[in]  vector3d  The vector to scale.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T>
Vector3D<T> operator*(const int32_t value, const Vector3D<T>& vector3d)
{
    return vector3d * value;
}

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Vector3D<T>> {
    std::size_t
    operator()(const utils::geometry3d::Vector3D<T>& k) const noexcept
    {
        return std::hash<T>()(k.getX()) ^ std::hash<T>()(k.getY())
            ^ std::hash<T>()(k.getZ());
    }
};
