#pragma once

#include "../Concepts.hpp"

namespace utils::geometry2d {

/**
 * @brief      Describes spacial coordinates in a 2-dimension system.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
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
     * \brief
     * \return
     */
    [[nodiscard]] constexpr T getX() const noexcept { return mX; }
    /**
     * \brief
     * \return
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
     * \brief Getter for structured binding
     * \tparam N
     * \return
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
    : std::integral_constant<std::size_t, 2> { };
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
