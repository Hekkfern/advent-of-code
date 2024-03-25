#include "Rock.hpp"

namespace aoc_2023_14 {

Rock::Rock(RockType type, utils::geometry2d::Point2D<> position)
    : mType{type}
    , mPosition{position}
{
}

} // namespace aoc_2023_14
