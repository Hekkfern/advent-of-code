#pragma once

#include "../Concepts.hpp"
#include "Point2D.hpp"
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
    explicit Vector2D(const Point2D<T>& origin, const Point2D<T>& destination)
        : mX{destination.getX() - origin.getX()}
        , mY{destination.getY() - origin.getY()}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Pair of coordinates (X,Y).
     */
    explicit Vector2D(const std::pair<T, T>& coords)
        : mX{coords.first}
        , mY{coords.second}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    std::array<T, 2U> getCoordinates() const { return {mX, mY}; }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    T getX() const { return mX; }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    T getY() const { return mY; }
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y).
     */
    std::array<uint64_t, 2U> size() const
    {
        return {std::abs(mX), std::abs(mY)};
    }
    /**
     * @brief      { function_description }
     *
     * @return     { description_of_the_return_value }
     */
    uint64_t range() const
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
    uint64_t distance() const
    {
        return static_cast<uint64_t>(std::abs(mX) + std::abs(mY));
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
    Vector2D getNormalized() const
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
    bool isZero() const { return mX == 0 && mY == 0; }
    /**
     * @brief      Determines if it is a horizontal vector, i.e. its coordinate
     *             Y is zero.
     *
     * @return     True if it is horizontal, False otherwise.
     */
    bool isHorizontal() const { return mY == 0; }
    /**
     * @brief      Determines if it is a vertical vector, i.e. its coordinate X
     *             is zero.
     *
     * @return     True if it is vertical, False otherwise.
     */
    bool isVertical() const { return mX == 0; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Vector2D& other) const
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
    Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D{mX + other.mX, mY + other.mY};
    }
    /**
     * @brief      Negation operator, which inverts the sign of both coordinates
     *             of the vector, i.e. inverts the direction of the vector.
     *
     * @return     The inverted vector.
     */
    Vector2D operator-() const { return Vector2D{-mX, -mY}; }
    /**
     * @brief      Subtraction operator, which subtracts the coordinates of
     *             both objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the subtraction.
     */
    Vector2D operator-(const Vector2D& other) const { return *this + (-other); }
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
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector2D)
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

} // namespace utils::geometry2d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Vector2D<T>> {
    std::size_t
    operator()(const utils::geometry2d::Vector2D<T>& k) const noexcept
    {
        return std::hash<T>()(k.getX()) ^ std::hash<T>()(k.getY());
    }
};