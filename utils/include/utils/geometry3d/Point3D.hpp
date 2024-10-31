#pragma once

#include "Coordinate3D.hpp"
#include "utils/Concepts.hpp"
#include <array>
#include <cstdint>
#include <ostream>

namespace utils::geometry3d {

template <SignedIntegerType T = int32_t>
class Point3D {
public:
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Point3D() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     * @param[in]  z     Coordinate Z.
     */
    constexpr explicit Point3D(T x, T y, T z)
        : mCoordinates{Coordinate3D<T>{x, y, z}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords     Coordinates.
     */
    constexpr explicit Point3D(Coordinate3D<T> const& coords)
        : mCoordinates{coords}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a group (X,Y,Z).
     */
    [[nodiscard]] constexpr Coordinate3D<T> getCoordinates() const
    {
        return mCoordinates;
    }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] constexpr T getX() const { return mCoordinates.getX(); }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] constexpr T getY() const { mCoordinates.getY(); }
    /**
     * @brief      Gets the coordinate Z.
     *
     * @return     The coordinate Z.
     */
    [[nodiscard]] constexpr T getZ() const { mCoordinates.getZ(); }
    /**
     * @brief Gets a list of all the colliding points.
     *
     * @return List of colliding points.
     */
    [[nodiscard]] constexpr std::array<Point3D, 6ULL>
    getNeighbors() const noexcept
    {
        return {
            Point3D{
                mCoordinates.getX(),
                mCoordinates.getY() + 1,
                mCoordinates.getZ()},
            Point3D{
                mCoordinates.getX() + 1,
                mCoordinates.getY(),
                mCoordinates.getZ()},
            Point3D{
                mCoordinates.getX(),
                mCoordinates.getY() - 1,
                mCoordinates.getZ()},
            Point3D{
                mCoordinates.getX() - 1,
                mCoordinates.getY() + 1,
                mCoordinates.getZ()},
            Point3D{
                mCoordinates.getX(),
                mCoordinates.getY(),
                mCoordinates.getZ() + 1},
            Point3D{
                mCoordinates.getX(),
                mCoordinates.getY(),
                mCoordinates.getZ() - 1}};
    }
    /**
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     */
    [[nodiscard]] constexpr Point3D setX(T const x) const noexcept
    {
        return Point3D{mCoordinates.setX(x)};
    }
    /**
     * @brief      Sets the coordinate Y.
     *
     * @param[in]  y     The coordinate Y.
     */
    [[nodiscard]] constexpr Point3D setY(T const y) const noexcept
    {
        return Point3D{mCoordinates.setY(y)};
    }
    /**
     * @brief      Sets the coordinate Z.
     *
     * @param[in]  z     The coordinate Z.
     */
    [[nodiscard]] constexpr Point3D setZ(T const z) const noexcept
    {
        return Point3D{mCoordinates.setZ(z)};
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(Point3D const& other) const = default;
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point3D operator-() const
    {
        return Point3D{
            -mCoordinates.getX(), -mCoordinates.getY(), -mCoordinates.getZ()};
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
    operator<<(std::ostream& os, Point3D<T> const& obj) noexcept
    {
        os << obj.toString();
        return os;
    }

    /**
     * Stores coordinate X, Y and Z.
     */
    Coordinate3D<T> mCoordinates{};
};

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Point3D<T>> {
    std::size_t
    operator()(utils::geometry3d::Point3D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
