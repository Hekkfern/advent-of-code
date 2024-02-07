#include "Almanac2.hpp"

#include <range/v3/algorithm/upper_bound.hpp>

namespace aoc_2023_5 {

utils::interval::IntervalSet<int64_t> convert(
    utils::interval::IntervalSet<int64_t> const& input,
    aoc_2023_5::RangeMap const& map)
{
    utils::interval::IntervalSet<int64_t> output;

    // Get the first relevant map
    auto it = ranges::upper_bound(
        map, Range{input[0].start, 0, 0}, std::less<>{});
    if (it != map.begin())
        it = std::prev(it);

    // For each seed range in the input (the ranges are already sorted)
    for (auto [start, size] : input) {
        while (size > 0) {
            if (it == map.end()) {
                // No conversion, no more mappings
                output.push_back({start, size});
                size = 0;
            } else if (start < it->input_offset) {
                // No conversion
                // (initial part of the range not covered by a mapping)
                int64_t actual = std::min(size, it->input_offset - start);
                output.push_back({start, actual});
                start += actual;
                size -= actual;
            } else if (start - it->input_offset >= it->size) {
                // The current mapping is no longer relevant
                ++it;
            } else {
                // Actual conversion
                int64_t actual = std::min(
                    (it->input_offset + it->size) - start, size);
                output.push_back(
                    {start - it->input_offset + it->output_offset, actual});
                start += actual;
                size -= actual;
            }
        }
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
