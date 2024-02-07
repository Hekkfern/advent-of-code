#pragma once

#include "RangeMap.hpp"
#include <cstdint>
#include <utils/interval/IntervalSet.hpp>
#include <vector>

namespace aoc_2023_5 {

class Almanac2 {
public:
    utils::interval::IntervalSet<int64_t> seeds{};
    RangeMap seed2SoilMap{};
    RangeMap soil2FertilizerMap{};
    RangeMap fertilizer2WaterMap{};
    RangeMap water2LightMap{};
    RangeMap light2TemperatureMap{};
    RangeMap temperature2HumidityMap{};
    RangeMap humidity2LocationMap{};

    Almanac2() = default;
    [[nodiscard]] utils::interval::IntervalSet<int64_t> getSeedRangeLocations(
        utils::interval::IntervalSet<int64_t> const& seedRange) const noexcept;
};

} // namespace aoc_2023_5
