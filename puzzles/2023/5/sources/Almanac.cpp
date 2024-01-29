#include "Almanac.hpp"

namespace {

uint32_t calculateOutputMap(
    std::unordered_map<uint32_t, uint32_t> const& map,
    uint32_t const id) noexcept
{
    auto const it{map.find(id)};
    if (it == map.cend()) {
        return id;
    }
    return it->second;
}

} // namespace

namespace aoc_2023_5 {

uint32_t Almanac::getSeedLocation(uint32_t const seed) const noexcept
{
    return calculateOutputMap(
        humidity2LocationMap,
        calculateOutputMap(
            temperature2HumidityMap,
            calculateOutputMap(
                light2TemperatureMap,
                calculateOutputMap(
                    water2LightMap,
                    calculateOutputMap(
                        fertilizer2WaterMap,
                        calculateOutputMap(
                            soil2FertilizerMap,
                            calculateOutputMap(seed2SoilMap, seed)))))));
}

} // namespace aoc_2023_5
