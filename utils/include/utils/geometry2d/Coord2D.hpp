#pragma once

#include "../Concepts.hpp"

namespace utils::geometry2d {

/**
 * @brief      Describes spacial coordinates in a 2-dimension system.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <IntegerType T = int32_t>
class Coord2D {
public:
    /**
     * @brief      Default constructor
     */
    constexpr explicit Coord2D() noexcept = default;
    /**
     * @brief      Parametrized constructor
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Coord2D(T x, T y) noexcept
        : mX{x}
        , mY{y}
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
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool operator==(Coord2D const& other) const noexcept
    {
        return mX == other.mX && mY == other.mY;
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
        }
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
    friend std::ostream& operator<<(std::ostream& os, Coord2D const& obj)
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

namespace std {

/* Support for structured binding */
template <class T>
struct tuple_size<utils::geometry2d::Coord2D<T>>
    : std::integral_constant<std::size_t, 2> {
};
/* Support for structured binding */
template <class T>
struct tuple_element<0, utils::geometry2d::Coord2D<T>> {
    using type = T;
};
/* Support for structured binding */
template <class T>
struct tuple_element<1, utils::geometry2d::Coord2D<T>> {
    using type = T;
};

} // namespace std
