#pragma once

#include <cstdint>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2023_3 {

struct Part {
    uint32_t partNumber{0U};
    utils::geometry2d::Point2D<> startPosition;
    utils::geometry2d::Point2D<> endPosition;

    Part(
        uint32_t pn,
        utils::geometry2d::Point2D<> start,
        utils::geometry2d::Point2D<> end);
};

struct Schematic {
    std::vector<Part> parts;
    std::vector<utils::geometry2d::Point2D<>> symbols;

    void merge(Schematic&& other) noexcept;
};

} // namespace aoc_2023_3
