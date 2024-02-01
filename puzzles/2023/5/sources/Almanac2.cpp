#include "Almanac2.hpp"

#include <range/v3/algorithm/upper_bound.hpp>

namespace aoc_2023_5 {

std::vector<SeedRange>
convert(std::vector<SeedRange> const& input, aoc_2023_5::RangeMap const& map)
{
    std::vector<SeedRange> output;

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
    std::ranges::sort(output, std::less<>{});
    return output;
}

std::vector<SeedRange>
Almanac2::getSeedRangeLocations(SeedRange seedRange) const noexcept
{
    // todo
    return std::vector<SeedRange>();
}

} // namespace aoc_2023_5
