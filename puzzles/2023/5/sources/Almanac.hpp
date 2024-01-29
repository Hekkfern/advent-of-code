#pragma once

#include <cstdint>
#include <unordered_map>

namespace aoc_2023_5 {

class Almanac {
public:
    std::vector<uint32_t> seeds;
    std::unordered_map<uint32_t, uint32_t> seed2SoilMap;
    std::unordered_map<uint32_t, uint32_t> soil2FertilizerMap;
    std::unordered_map<uint32_t, uint32_t> fertilizer2WaterMap;
    std::unordered_map<uint32_t, uint32_t> water2LightMap;
    std::unordered_map<uint32_t, uint32_t> light2TemperatureMap;
    std::unordered_map<uint32_t, uint32_t> temperature2HumidityMap;
    std::unordered_map<uint32_t, uint32_t> humidity2LocationMap;

    [[nodiscard]] uint32_t getSeedLocation(uint32_t seed) const noexcept;
};

} // namespace aoc_2023_5
