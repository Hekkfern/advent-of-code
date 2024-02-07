#pragma once

#include "RangeMap.hpp"
#include <cstdint>
#include <vector>

namespace aoc_2023_5 {

class Almanac {
public:
    std::vector<int64_t> seeds{};
    RangeMap seed2SoilMap{};
    RangeMap soil2FertilizerMap{};
    RangeMap fertilizer2WaterMap{};
    RangeMap water2LightMap{};
    RangeMap light2TemperatureMap{};
    RangeMap temperature2HumidityMap{};
    RangeMap humidity2LocationMap{};

    Almanac() = default;
    [[nodiscard]] int64_t getSeedLocation(int64_t seed) const noexcept;
};

} // namespace aoc_2023_5
