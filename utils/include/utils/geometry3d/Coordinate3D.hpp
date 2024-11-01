#pragma once

#include "../Hash.hpp"
#include "utils/Concepts.hpp"

namespace utils::geometry3d {

template <IntegerType T = int32_t>
class Coordinate3D {
public:
    /**
     * @brief      Default constructor
     */
    constexpr explicit Coordinate3D() noexcept = default;
    /**
     * @brief      Parametrized constructor
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Coordinate3D(T x, T y, T z) noexcept
        : mX{x}
        , mY{y}
        , mZ{z}
    {
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
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Coordinate3D setX(T const x) const noexcept
    {
        Coordinate3D result{*this};
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
    [[nodiscard]] constexpr Coordinate3D setY(T const y) const noexcept
    {
        Coordinate3D result{*this};
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
    [[nodiscard]] constexpr Coordinate3D setZ(T const z) const noexcept
    {
        Coordinate3D result{*this};
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
    [[nodiscard]] constexpr bool
    operator==(Coordinate3D const& other) const noexcept
        = default;
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
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
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, mX);
        utils::hash::hash_combine(seed, mY);
        return seed;
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os    The output stream.
     * @param[in]  obj   The instance.
     *
     * @return     The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Coordinate3D const& obj)
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

template <IntegerType T>
struct std::hash<utils::geometry3d::Coordinate3D<T>> {
    std::size_t operator()(utils::geometry3d::Coordinate3D<T> const& obj) const
    {
        return obj.calculateHash();
    }
};

/* Support for structured binding */
template <class T>
struct std::tuple_size<utils::geometry3d::Coordinate3D<T>>
    : std::integral_constant<std::size_t, 3> { };
template <class T>
struct std::tuple_element<0, utils::geometry3d::Coordinate3D<T>> {
    using type = T;
};
template <class T>
struct std::tuple_element<1, utils::geometry3d::Coordinate3D<T>> {
    using type = T;
};
template <class T>
struct std::tuple_element<2, utils::geometry3d::Coordinate3D<T>> {
    using type = T;
};
