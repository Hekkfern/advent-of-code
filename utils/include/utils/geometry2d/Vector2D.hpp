#pragma once

#include "../Concepts.hpp"
#include "../Hash.hpp"
#include "Point2D.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>

namespace utils::geometry2d {

/**
 * @brief      Describes a Vector (i.e. a directional arrow) in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Vector2D {
public:
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Vector2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Vector2D(T const x, T const y)
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
    constexpr explicit Vector2D(
        Point2D<T> const& origin, Point2D<T> const& destination) noexcept
        : mX{destination.getX() - origin.getX()}
        , mY{destination.getY() - origin.getY()}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Coordinates.
     */
    constexpr explicit Vector2D(Coordinate2D<T> const coords) noexcept
        : mX{coords.getX()}
        , mY{coords.getY()}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  point  Point.
     */
    constexpr explicit Vector2D(Point2D<T> const p) noexcept
        : mX{p.getX()}
        , mY{p.getY()}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] constexpr Coordinate2D<T> getCoordinates() const noexcept
    {
        return Coordinate2D<T>{mX, mY};
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
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y).
     */
    [[nodiscard]] constexpr std::array<uint64_t, 2ULL> size() const noexcept
    {
        return {
            static_cast<uint64_t>(std::abs(mX)),
            static_cast<uint64_t>(std::abs(mY))};
    }
    /**
     * @brief      Gets the maximum, absolute coordinate between X and Y.
     *
     * @return     The maximum, absolute coordinate value.
     */
    [[nodiscard]] constexpr uint64_t range() const noexcept
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
    [[nodiscard]] constexpr uint64_t distance() const noexcept
    {
        return static_cast<uint64_t>(std::abs(mX))
            + static_cast<uint64_t>(std::abs(mY));
    }
    /**
     * @brief      Modifies the vector so the lengths becomes one (positive or
     *             negative) up most, keeping the same direction.
     *
     * @return     The normalized vector.
     */
    [[nodiscard]] constexpr Vector2D normalize() const noexcept
    {
        Vector2D result{*this};
        // saturate X
        result.mX = std::clamp(mX, -1, 1);
        // saturate Y
        result.mY = std::clamp(mY, -1, 1);
        return result;
    }
    /**
     * @brief      Determines if the vector is empty, i.e., both coordinates are
     *             zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    [[nodiscard]] constexpr bool isZero() const noexcept
    {
        return mX == 0 && mY == 0;
    }
    /**
     * @brief      Determines if it is a horizontal vector, i.e. its coordinate
     *             Y is zero.
     *
     * @return     True if it is horizontal, False otherwise.
     */
    [[nodiscard]] constexpr bool isHorizontal() const noexcept
    {
        return mY == 0;
    }
    /**
     * @brief      Determines if it is a vertical vector, i.e. its coordinate X
     *             is zero.
     *
     * @return     True if it is vertical, False otherwise.
     */
    [[nodiscard]] constexpr bool isVertical() const noexcept { return mX == 0; }
    /**
     * @brief      Determines if it is a diagonal vector, i.e. its coordinate X
     *             is equal to its coordinate Y.
     *
     * @return     True if it is diagonal, False otherwise.
     */
    [[nodiscard]] constexpr bool isDiagonal() const noexcept
    {
        return std::abs(static_cast<std::intmax_t>(mX))
            == std::abs(static_cast<std::intmax_t>(mY));
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(Vector2D<T> const& other) const noexcept
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
    [[nodiscard]] constexpr Vector2D
    operator+(Vector2D const& other) const noexcept
    {
        return Vector2D{mX + other.mX, mY + other.mY};
    }
    /**
     * @brief      Negation operator, which inverts the sign of both coordinates
     *             of the vector, i.e. inverts the direction of the vector.
     *
     * @return     The inverted vector.
     */
    [[nodiscard]] constexpr Vector2D operator-() const noexcept
    {
        return Vector2D{-mX, -mY};
    }
    /**
     * @brief      Subtraction operator, which subtracts the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the subtraction.
     */
    [[nodiscard]] constexpr Vector2D
    operator-(Vector2D<T> const& other) const noexcept
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
    [[nodiscard]] constexpr static Vector2D<T> create(U x, U y) noexcept
    {
        return Vector2D<T>{static_cast<T>(x), static_cast<T>(y)};
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
    {
        return "(" + std::to_string(mX) + "," + std::to_string(mY) + ")";
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
        return seed;
    }
    /**
     * @brief      Calculates the angle of the vector.
     *
     * @return     Angle expressed in radians.
     */
    [[nodiscard]] double angle() const noexcept { return std::atan2(mY, mX); }

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
    operator<<(std::ostream& os, Vector2D<T> const& obj) noexcept
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
};

/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  vector2d  The vector to scale.
 * @param[in]  value     The scalar value to scale by.
 *
 * @tparam     T         Type of the coordinate values.
 * @tparam     U         Type of the scalar value.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T, IntegerType U>
[[nodiscard]] constexpr Vector2D<T>
operator*(Vector2D<T> const& vector2d, U const value) noexcept
{
    return Vector2D<T>{
        static_cast<T>(value) * vector2d.getX(),
        static_cast<T>(value) * vector2d.getY()};
}
/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  value     The scalar value to scale by.
 * @param[in]  vector2d  The vector to scale.
 *
 * @tparam     T         Type of the coordinate values.
 * @tparam     U         Type of the scalar value.
 *
 * @return     Scaled vector by a scalar.
 */
template <SignedIntegerType T, IntegerType U>
[[nodiscard]] constexpr Vector2D<T>
operator*(U const value, Vector2D<T> const& vector2d) noexcept
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
