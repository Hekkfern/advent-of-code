#include "Schematic.hpp"

namespace aoc_2023_3 {

Part::Part(
    uint32_t pn,
    utils::geometry2d::Point2D<> start,
    utils::geometry2d::Point2D<> end)
    : partNumber{pn}
    , startPosition{start}
    , endPosition{end}
{
}

void Schematic::merge(Schematic&& other) noexcept
{
    parts.reserve(parts.size() + other.parts.size());
    std::move(
        other.parts.begin(), other.parts.end(), std::back_inserter(parts));
}

} // namespace aoc_2023_3
