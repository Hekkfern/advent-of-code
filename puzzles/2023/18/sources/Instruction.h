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
     * @param[in] c Color code.
     */
    Instruction(
        utils::geometry2d::Direction2D const& d,
        uint32_t const s,
        std::string_view const c)
        : direction{d}
        , steps{s}
        , color{c}
    {
    }
    /**
     * Direction to move. It can be Up, Down, Left or Right.
     */
    utils::geometry2d::Direction2D direction;
    /**
     * Number of steps to move in the given direction. Value > 0.
     */
    uint32_t steps;
    /**
     * Stores the RGB color code. For example, "70c710".
     */
    std::string color;
};

} // namespace aoc_2023_18
