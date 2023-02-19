#pragma once

#include <cstdint>
#include <utils/geometry2d/Direction.hpp>

namespace aoc_2022_9 {

using namespace utils::geometry2d;

struct RopeInstruction {
    Direction mDirection;
    uint32_t mQuantity;
};

} // namespace aoc_2022_9
