#pragma once

#include "RockType.hpp"
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2023_14 {

class Rock {
public:
    Rock(RockType type, utils::geometry2d::Point2D<> position);

private:
    RockType mType;
    utils::geometry2d::Point2D<> mPosition;
};

} // namespace aoc_2023_14
