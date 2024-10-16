#pragma once

#include <functional>
#include <utils/Hash.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_17 {

struct State {
    State(
        utils::geometry2d::Coordinate2D<std::size_t> const& position,
        utils::geometry2d::Direction2D const& direction,
        uint32_t steps,
        uint32_t heatLoss);
    bool operator==(State const& b) const = default;

    utils::geometry2d::Coordinate2D<std::size_t> position;
    utils::geometry2d::Direction2D direction;
    uint32_t steps;
    uint32_t heatLoss;
};

} // namespace aoc_2023_17

template <>
struct std::hash<aoc_2023_17::State> {
    std::size_t operator()(aoc_2023_17::State const& obj) const
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, obj.position);
        utils::hash::hash_combine(seed, obj.direction);
        utils::hash::hash_combine(seed, obj.steps);
        utils::hash::hash_combine(seed, obj.heatLoss);
        return seed;
    }
};