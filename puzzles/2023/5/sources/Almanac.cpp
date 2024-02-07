#include "Almanac.hpp"

namespace aoc_2023_5 {

int64_t Almanac::getSeedLocation(int64_t const seed) const noexcept
{
    return humidity2LocationMap.get(temperature2HumidityMap.get(
        light2TemperatureMap.get(water2LightMap.get(fertilizer2WaterMap.get(
            soil2FertilizerMap.get(seed2SoilMap.get(seed)))))));
}

} // namespace aoc_2023_5
