#include "Almanac2.hpp"

namespace aoc_2023_5 {

utils::interval::IntervalSet<int64_t>
convert(utils::interval::IntervalSet<int64_t> const& input, RangeMap const& map)
{
    utils::interval::IntervalSet<int64_t> output;
    // For each input range in the input (the ranges are already sorted)
    for (auto const& inputInterval : input.get()) {
        output = output.join(map.convert(inputInterval));
    }
    return output;
}

utils::interval::IntervalSet<int64_t> Almanac2::getSeedRangeLocations(
    utils::interval::IntervalSet<int64_t> const& seedRange) const noexcept
{
    return convert(
        convert(
            convert(
                convert(
                    convert(
                        convert(
                            convert(
                                convert(seedRange, seed2SoilMap),
                                soil2FertilizerMap),
                            soil2FertilizerMap),
                        fertilizer2WaterMap),
                    water2LightMap),
                light2TemperatureMap),
            temperature2HumidityMap),
        humidity2LocationMap);
}

} // namespace aoc_2023_5
