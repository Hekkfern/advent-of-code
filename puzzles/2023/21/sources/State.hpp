#pragma once

#include <functional>
#include <utils/Hash.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_21 {

struct State {
    State(
        utils::geometry2d::Coordinate2D<std::size_t> const& position,
        uint32_t steps);
    bool operator==(State const& other) const = default;

    utils::geometry2d::Coordinate2D<std::size_t> position;
    uint32_t steps;
};

} // namespace aoc_2023_21

template <>
struct std::hash<aoc_2023_21::State> {
    std::size_t operator()(aoc_2023_21::State const& obj) const
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, obj.position);
        utils::hash::hash_combine(seed, obj.steps);
        return seed;
    }
};