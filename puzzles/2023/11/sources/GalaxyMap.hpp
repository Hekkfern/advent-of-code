#pragma once

#include <utils/geometry2d/Point2D.hpp>
#include <vector>

namespace aoc_2023_11 {

class GalaxyMap {
public:
    GalaxyMap() = default;

    std::vector<utils::geometry2d::Point2D<int32_t>> mGalaxies{};
    std::vector<int32_t> mEmptyRows{};
    std::vector<int32_t> mEmptyColumns{};
};

} // namespace aoc_2023_11
