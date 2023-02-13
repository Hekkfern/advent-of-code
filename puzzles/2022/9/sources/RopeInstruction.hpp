#pragma once

#include <utils/geometry2d/Direction.hpp>
#include <cstdint>

namespace aoc_2022_9 {

struct RopeInstruction {
    Direction mDirection;
    uint32_t mQuantity;
};

} // namespace aoc_2022_9
