#pragma once

#include <utils/Hash.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_16 {

struct Beam {
    utils::geometry2d::Coordinate2D<std::size_t> coordinates;
    utils::geometry2d::Direction2D direction;

    /**
     * @brief      Default constructor
     */
    Beam(
        utils::geometry2d::Coordinate2D<std::size_t> const& coordinates,
        utils::geometry2d::Direction2D const& direction)
        : coordinates{coordinates}
        , direction{direction}
    {
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(Beam const& other) const noexcept
    {
        return coordinates == other.coordinates && direction == other.direction;
    }
    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, coordinates);
        utils::hash::hash_combine(seed, direction);
        return seed;
    }
};

} // namespace aoc_2023_16

template <>
struct std::hash<aoc_2023_16::Beam> {
    std::size_t operator()(aoc_2023_16::Beam const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};
