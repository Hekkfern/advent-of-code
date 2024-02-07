#include "Almanac.hpp"

namespace aoc_2023_5 {

int64_t Almanac::getSeedLocation(int64_t const seed) const noexcept
{
    return humidity2LocationMap.convert(
        temperature2HumidityMap.convert(light2TemperatureMap.convert(
            water2LightMap.convert(fertilizer2WaterMap.convert(
                soil2FertilizerMap.convert(seed2SoilMap.convert(seed)))))));
}

} // namespace aoc_2023_5
