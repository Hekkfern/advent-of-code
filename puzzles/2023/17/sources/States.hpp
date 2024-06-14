#pragma once

#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_17 {

struct States {
    utils::geometry2d::Coordinate2D<std::size_t> position;
    utils::geometry2d::Direction2D direction;
    int64_t heatLoss;
    int32_t steps;
};

} // namespace aoc_2023_17
