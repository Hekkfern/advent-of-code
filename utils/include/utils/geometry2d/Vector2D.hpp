#pragma once

#include "../Concepts.hpp"
#include "Point2D.hpp"
#include <algorithm>
#include <array>
#include <cstdint>

namespace utils::geometry2d {

/**
 * @brief      This class describes a Vector (i.e. a directional arrow) in 2D
 *             space.
 */
template <SignedIntegerType T = int32_t>
class Vector2D {
public:
    /**
     * @brief      Default constructor.
     */
    explicit Vector2D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    explicit Vector2D(T x, T y)
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin       The origin point.
     * @param[in]  destination  The destination point.
     */
    explicit Vector2D(Point2D<T> const& origin, Point2D<T> const& destination)
        : mX{destination.getX() - origin.getX()}
        , mY{destination.getY() - origin.getY()}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Coordinates.
     */
    explicit Vector2D(Coord2D<T> const coords)
        : mX{coords.mX}
        , mY{coords.mY}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] Coord2D<T> getCoordinates() const { return {mX, mY}; }
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
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y).
     */
    [[nodiscard]] std::array<uint64_t, 2U> size() const
    {
        return {
            static_cast<uint64_t>(std::abs(mX)),
            static_cast<uint64_t>(std::abs(mY))};
    }
    /**
     * @brief      { function_description }
     *
     * @return     { description_of_the_return_value }
     */
    [[nodiscard]] uint64_t range() const
    {
        return static_cast<uint64_t>(std::max(std::abs(mX), std::abs(mY)));
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
        return static_cast<uint64_t>(std::abs(mX))
            + static_cast<uint64_t>(std::abs(mY));
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
    }
    /**
     * @brief      Creates a normalized vector from this one.
     *
     * @return     The normalized vector.
     */
    [[nodiscard]] Vector2D getNormalized() const
    {
        Vector2D vector2D(*this);
        vector2D.normalize();
        return vector2D;
    }
    /**
     * @brief      Determines if the vector is empty, i.e., both coordinates are
     *             zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    [[nodiscard]] bool isZero() const { return mX == 0 && mY == 0; }
    /**
     * @brief      Determines if it is a horizontal vector, i.e. its coordinate
     *             Y is zero.
     *
     * @return     True if it is horizontal, False otherwise.
     */
    [[nodiscard]] bool isHorizontal() const { return mY == 0; }
    /**
     * @brief      Determines if it is a vertical vector, i.e. its coordinate X
     *             is zero.
     *
     * @return     True if it is vertical, False otherwise.
     */
    [[nodiscard]] bool isVertical() const { return mX == 0; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(Vector2D const& other) const
    {
        return (mX == other.mX) && (mY == other.mY);
    }
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] Vector2D operator+(Vector2D const& other) const
    {
        return Vector2D{mX + other.mX, mY + other.mY};
    }
    /**
     * @brief      Negation operator, which inverts the sign of both coordinates
     *             of the vector, i.e. inverts the direction of the vector.
     *
     * @return     The inverted vector.
     */
    [[nodiscard]] Vector2D operator-() const { return Vector2D{-mX, -mY}; }
    /**
     * @brief      Subtraction operator, which subtracts the coordinates of
     *             both objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the subtraction.
     */
    [[nodiscard]] Vector2D operator-(Vector2D const& other) const
    {
        return *this + (-other);
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
     * @return     New vector.
     */
    template <std::integral U>
    [[nodiscard]] static Vector2D create(U x, U y)
    {
        return Vector2D{static_cast<T>(x), static_cast<T>(y)};
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param      os        The output stream.
     * @param[in]  vector2D  The vector.
     *
     * @return     The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Vector2D const& vector2D)
    {
        os << '(' << vector2D.mX << ',' << vector2D.mY << ')';
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
};

/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  vector2d  The vector to scale.
 * @param[in]  value     The scalar value to scale by.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T>
[[nodiscard]] Vector2D<T>
operator*(Vector2D<T> const& vector2d, int32_t const value)
{
    return Vector2D<T>{value * vector2d.getX(), value * vector2d.getY()};
}
/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  value     The scalar value to scale by.
 * @param[in]  vector2d  The vector to scale.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T>
[[nodiscard]] Vector2D<T>
operator*(int32_t const value, Vector2D<T> const& vector2d)
{
    return vector2d * value;
}

} // namespace utils::geometry2d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Vector2D<T>> {
    std::size_t
    operator()(utils::geometry2d::Vector2D<T> const& k) const noexcept
    {
        return std::hash<T>()(k.getX()) ^ std::hash<T>()(k.getY());
    }
};