#pragma once

#include "utils/Concepts.hpp"
#include <array>
#include <cstdint>
#include <ostream>
#include <utils/Hash.hpp>

namespace utils::geometry3d {

/**
 * @brief      Describes a point in 3D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Point3D {
public:
    static constexpr uint32_t Dimension{3U};
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Point3D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     * @param[in]  z     Coordinate Z.
     */
    constexpr explicit Point3D(T x, T y, T z) noexcept
        : mX{x}
        , mY{y}
        , mZ{z}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a group (X,Y,Z).
     */
    [[nodiscard]] constexpr std::array<T, Dimension>
    getCoordinates() const noexcept
    {
        return std::to_array({mX, mY, mZ});
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
     * @brief Gets a list of all the colliding points.
     *
     * @return List of colliding points.
     */
    [[nodiscard]] constexpr std::array<Point3D, 2 * Dimension>
    getNeighbors() const noexcept
    {
        return {
            Point3D{mX, mY + 1, mZ},
            Point3D{mX + 1, mY, mZ},
            Point3D{mX, mY - 1, mZ},
            Point3D{mX - 1, mY + 1, mZ},
            Point3D{mX, mY, mZ + 1},
            Point3D{mX, mY, mZ - 1}};
    }
    /**
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point3D setX(T const x) const noexcept
    {
        Point3D result{*this};
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
    [[nodiscard]] constexpr Point3D setY(T const y) const noexcept
    {
        Point3D result{*this};
        result.mY = y;
        return result;
    }
    /**
     * @brief      Sets the coordinate Z.
     *
     * @param[in]  z     The coordinate Z.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point3D setZ(T const z) const noexcept
    {
        Point3D result{*this};
        result.mZ = z;
        return result;
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool operator==(Point3D const& other) const noexcept
        = default;
    /**
     * @brief      Invert the coordinates respect origin.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point3D invert() const noexcept
    {
        return Point3D{-mX, -mY, -mZ};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Point3D operator-() const noexcept
    {
        return invert();
    }
    /**
     * @brief      Mirror respect X-Y plane.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point3D mirrorXY() const noexcept
    {
        return Point3D{mX, mY, -mZ};
    }
    /**
     * @brief      Mirror respect X-Z plane.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point3D mirrorXZ() const noexcept
    {
        return Point3D{mX, -mY, mZ};
    }
    /**
     * @brief      Mirror respect Y-Z plane.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point3D mirrorYZ() const noexcept
    {
        return Point3D{-mX, mY, mZ};
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
    [[nodiscard]] constexpr static Point3D create(U x, U y, U z) noexcept
    {
        return Point3D{static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)};
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const noexcept
    {
        return "[" + std::to_string(mX) + "," + std::to_string(mY) + ","
            + std::to_string(mZ) + "]";
    }
    /**
     * @brief      Getter for structured binding
     *
     * @tparam     N     Number of tuple-like parameters.
     *
     * @return     The value of the internal variable, according to @p N.
     */
    template <std::size_t N>
    [[nodiscard]] decltype(auto) get() const
    {
        if constexpr (N == 0) {
            return mX;
        } else if constexpr (N == 1) {
            return mY;
        } else if constexpr (N == 2) {
            return mZ;
        }
    }
    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] constexpr std::size_t calculateHash() const noexcept
    {
        std::size_t seed{0ULL};
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
    operator<<(std::ostream& os, Point3D<T> const& obj) noexcept
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

} // namespace utils::geometry3d

template <SignedIntegerType T>
struct std::hash<utils::geometry3d::Point3D<T>> {
    std::size_t
    operator()(utils::geometry3d::Point3D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};

/* Support for structured binding */
template <class T>
struct std::tuple_size<utils::geometry3d::Point3D<T>>
    : std::integral_constant<
          std::size_t,
          utils::geometry3d::Point3D<T>::Dimension> { };
template <class T>
struct std::tuple_element<0, utils::geometry3d::Point3D<T>> {
    using type = T;
};
template <class T>
struct std::tuple_element<1, utils::geometry3d::Point3D<T>> {
    using type = T;
};
template <class T>
struct std::tuple_element<2, utils::geometry3d::Point3D<T>> {
    using type = T;
};
