#pragma once

#include "../Concepts.hpp"
#include "Coordinate2D.hpp"
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
    constexpr explicit Point2D(T x, T y) noexcept
        : mCoordinates{Coordinate2D<T>{x, y}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Coordinates.
     */
    constexpr explicit Point2D(Coordinate2D<T> const& coords) noexcept
        : mCoordinates{coords}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] constexpr Coordinate2D<T> getCoordinates() const noexcept
    {
        return mCoordinates;
    }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] constexpr T getX() const noexcept
    {
        return mCoordinates.getX();
    }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] constexpr T getY() const noexcept
    {
        return mCoordinates.getY();
    }
    /**
     * @brief      Gets a list of all the colliding points.
     *
     * @return     List of colliding points.
     */
    [[nodiscard]] constexpr std::array<Point2D, 4ULL>
    getNeighbors() const noexcept
    {
        return {
            Point2D{mCoordinates.getX(), mCoordinates.getY() + 1},
            Point2D{mCoordinates.getX() + 1, mCoordinates.getY()},
            Point2D{mCoordinates.getX(), mCoordinates.getY() - 1},
            Point2D{mCoordinates.getX() - 1, mCoordinates.getY() + 1}};
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
        return Point2D{mCoordinates.setX(x)};
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
        return Point2D{mCoordinates.setY(y)};
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
        return mCoordinates == other.mCoordinates;
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Point2D operator-() const noexcept
    {
        return Point2D{-mCoordinates.getX(), -mCoordinates.getY()};
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
        return mCoordinates.toString();
    }
    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        return mCoordinates.calculateHash();
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
     * Stores coordinate X and Y.
     */
    Coordinate2D<T> mCoordinates{};
};

} // namespace utils::geometry2d

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Point2D<T>> {
    std::size_t
    operator()(utils::geometry2d::Point2D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
