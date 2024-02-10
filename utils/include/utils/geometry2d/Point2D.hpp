#pragma once

#include "../Concepts.hpp"
#include "Coord2D.hpp"
#include <array>
#include <cstdint>
#include <ostream>

namespace utils::geometry2d {

/**
 * @brief      Describes a point in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Point2D {
public:
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Point2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Point2D(T const x, T const y) noexcept
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Coordinates.
     */
    constexpr explicit Point2D(Coord2D<T> const coords) noexcept
        : mX{coords.getX()}
        , mY{coords.getY()}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] constexpr Coord2D<T> getCoordinates() const noexcept
    {
        return Coord2D<T>{mX, mY};
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
     * @brief      Gets a list of all the colliding points.
     *
     * @return     List of colliding points.
     */
    [[nodiscard]] constexpr std::array<Point2D, 4ULL>
    getNeighbors() const noexcept
    {
        return {
            Point2D{mX, mY + 1},
            Point2D{mX + 1, mY},
            Point2D{mX, mY - 1},
            Point2D{mX - 1, mY + 1}};
    }
    /**
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point2D setX(T const x) const noexcept
    {
        Point2D result{*this};
        result.mX = x;
        return result;
    }
    /**
     * @brief      Sets the coordinate Y.
     *
     * @param[in]  y     The coordinate Y.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point2D setY(T const y) const noexcept
    {
        Point2D result{*this};
        result.mY = y;
        return result;
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(Point2D<T> const& other) const noexcept
    {
        return mX == other.mX && mY == other.mY;
    }
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] constexpr Point2D
    operator+(Point2D const& other) const noexcept
    {
        return Point2D{mX + other.mX, mY + other.mY};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Point2D operator-() const noexcept
    {
        return Point2D{-mX, -mY};
    }
    /**
     * @brief      Subtraction operator.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Point2D
    operator-(Point2D const& other) const noexcept
    {
        return *this + (-other);
    }
    /**
     * @brief      Factory method to create a new Point based on the selected
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
    [[nodiscard]] constexpr static Point2D<T> create(U x, U y) noexcept
    {
        return Point2D{static_cast<T>(x), static_cast<T>(y)};
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
    {
        return "[" + std::to_string(mX) + "," + std::to_string(mY) + "]";
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
    operator<<(std::ostream& os, Point2D<T> const& obj) noexcept
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

} // namespace utils::geometry2d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Point2D<T>> {
    std::size_t
    operator()(utils::geometry2d::Point2D<T> const& k) const noexcept
    {
        return std::hash<T>()(k.getX()) ^ std::hash<T>()(k.getY());
    }
};
