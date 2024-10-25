#include "State.hpp"

namespace aoc_2023_21 {

State::State(
    utils::geometry2d::Coordinate2D<std::size_t> const& position,
    uint32_t const steps)
    : position(position)
    , steps(steps)
{
}

} // namespace aoc_2023_17