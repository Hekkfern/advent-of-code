#pragma once

#include <string>
#include <string_view>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_18 {

struct Instruction {
    /**
     * @brief Construct a new object.
     *
     * @param[in] d Direction to move.
     * @param[in] s Steps to move.
     */
    Instruction(
        utils::geometry2d::Direction2D const& d,
        uint64_t const s)
        : direction{d}
        , steps{s}
    {
    }
    /**
     * Direction to move. It can be Up, Down, Left or Right.
     */
    utils::geometry2d::Direction2D direction;
    /**
     * Number of steps to move in the given direction. Value > 0.
     */
    uint64_t steps;
};

} // namespace aoc_2023_18
