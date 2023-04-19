#pragma once

#include "../Concepts.hpp"
#include "Coord3D.hpp"
#include <array>
#include <cstdint>
#include <ostream>
#include <vector>

namespace utils::geometry3d {

template <SignedIntegerType T = int32_t>
class Point3D {
public:
    /**
     * @brief      Default constructor.
     */
    explicit Point3D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     * @param[in]  z     Coordinate Z.
     */
    explicit Point3D(T x, T y, T z)
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
    explicit Point3D(const Coord3D<T> coords)
        : mX{coords.mX}
        , mY{coords.mY}
        , mZ{coords.mZ}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a group (X,Y,Z).
     */
    [[nodiscard]] Coord3D<T> getCoordinates() const
    {
        return {mX, mY, mZ};
    }
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
     * @brief Gets a list of all the colliding points.
     *
     * @return List of colliding points.
     */
    [[nodiscard]] std::vector<Point3D<T>> getNeighbors() const noexcept
    {
        return std::vector<Point3D<T>>{
            Point3D{mX, mY + 1, mZ},
            Point3D{mX + 1, mY, mZ},
            Point3D{mX, mY - 1, mZ},
            Point3D{mX - 1, mY + 1, mZ},
            Point3D{mX, mY, mZ + 1},
            Point3D{mX, mY, mZ - 1}};
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(const Point3D& other) const
    {
        return (mX == other.mX) && (mY == other.mY) && (mZ == other.mZ);
    }
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] Point3D operator+(const Point3D& other) const
    {
        return Point3D{mX + other.mX, mY + other.mY, mZ + other.mZ};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point3D operator-() const { return Point3D{-mX, -mY, -mZ}; }
    /**
     * @brief      Subtraction operator.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point3D operator-(const Point3D& other) const
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
    [[nodiscard]] static Point3D create(U x, U y, U z)
    {
        return Point3D{static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)};
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Point3D& point2d)
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

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Point3D<T>> {
    std::size_t
    operator()(const utils::geometry3d::Point3D<T>& k) const noexcept
    {
        return std::hash<T>()(k.getX()) ^ std::hash<T>()(k.getY())
            ^ std::hash<T>()(k.getZ());
    }
};
