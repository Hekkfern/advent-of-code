#pragma once

#include <functional>
#include <utils/Hash.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2023_17 {

struct Node {
    Node(
        utils::geometry2d::Coordinate2D<std::size_t> p,
        utils::geometry2d::Direction2D d,
        uint32_t s)
        : position{p}
        , direction{d}
        , steps{s}
    {
    }
    bool operator==(Node const& other) const = default;

    utils::geometry2d::Coordinate2D<std::size_t> position;
    utils::geometry2d::Direction2D direction;
    uint32_t steps;
};

} // namespace aoc_2023_17

template <>
struct std::hash<aoc_2023_17::Node> {
    std::size_t operator()(aoc_2023_17::Node const& obj) const
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, obj.position);
        utils::hash::hash_combine(seed, obj.direction);
        utils::hash::hash_combine(seed, obj.steps);
        return seed;
    }
};
