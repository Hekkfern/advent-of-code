#include "State.h"

namespace aoc_2023_17 {

State::State(
    utils::geometry2d::Coordinate2D<std::size_t> const& position,
    utils::geometry2d::Direction2D const& direction,
    int32_t const steps,
    int32_t const heatLoss)
    : position(position)
    , direction(direction)
    , steps(steps)
    , heatLoss(heatLoss)
{
}

} // namespace aoc_2023_17