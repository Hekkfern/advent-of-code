#pragma once

#include "RangeMap.hpp"
#include "SeedRange.hpp"
#include <cstdint>
#include <vector>

namespace aoc_2023_5 {

class Almanac2 {
public:
    std::vector<SeedRange> seeds{};
    RangeMap seed2SoilMap{};
    RangeMap soil2FertilizerMap{};
    RangeMap fertilizer2WaterMap{};
    RangeMap water2LightMap{};
    RangeMap light2TemperatureMap{};
    RangeMap temperature2HumidityMap{};
    RangeMap humidity2LocationMap{};

    Almanac2() = default;
    [[nodiscard]] std::vector<SeedRange>
    getSeedRangeLocations(SeedRange seedRange) const noexcept;
};

} // namespace aoc_2023_5
