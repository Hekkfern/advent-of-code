#pragma once

#include "../Concepts.hpp"
#include "Coord2D.hpp"
#include <array>
#include <cstdint>
#include <ostream>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      This class describes a point in 2D space.
 */
template <SignedIntegerType T = int32_t>
class Point2D {
public:
    /**
     * @brief      Default constructor.
     */
    explicit Point2D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    explicit Point2D(const T x, const T y)
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Coordinates.
     */
    explicit Point2D(Coord2D<T> const coords)
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
     * @brief Gets a list of all the colliding points.
     *
     * @return List of colliding points.
     */
    [[nodiscard]] std::vector<Point2D<T>> getNeighbors() const noexcept
    {
        return std::vector<Point2D<T>>{
            Point2D{mX, mY + 1},
            Point2D{mX + 1, mY},
            Point2D{mX, mY - 1},
            Point2D{mX - 1, mY + 1}};
    }
    /**
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     */
    void setX(const T x) { mX = x; }
    /**
     * @brief      Sets the coordinate Y.
     *
     * @param[in]  y     The coordinate Y.
     */
    void setY(const T y) { mY = y; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(Point2D const& other) const
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
    [[nodiscard]] Point2D operator+(Point2D const& other) const
    {
        return Point2D{mX + other.mX, mY + other.mY};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point2D operator-() const { return Point2D{-mX, -mY}; }
    /**
     * @brief      Subtraction operator.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point2D operator-(Point2D const& other) const
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
    [[nodiscard]] static Point2D create(U x, U y)
    {
        return Point2D{static_cast<T>(x), static_cast<T>(y)};
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]      os       The output stream.
     * @param[in]  point2d  The point.
     *
     * @return     The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Point2D const& point2d)
    {
        os << '(' << point2d.mX << ',' << point2d.mY << ')';
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