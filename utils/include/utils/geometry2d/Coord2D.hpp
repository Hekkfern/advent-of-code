#pragma once

#include "../Concepts.hpp"

namespace utils::geometry2d {

template <SignedIntegerType T = int32_t>
struct Coord2D {
    /**
     * @brief Default constructor
     */
    Coord2D() = default;
    /**
     * @brief Parametrized constructor
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    Coord2D(T x, T y)
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(const Coord2D<>& other) const
    {
        return mX == other.mX && mY == other.mY;
    }
    /**
     * Stores coordinate X.
     */
    const T mX{0};
    /**
     * Stores coordinate Y.
     */
    const T mY{0};
};

} // namespace utils::geometry2d
