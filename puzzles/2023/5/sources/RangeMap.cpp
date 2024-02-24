#include "RangeMap.hpp"

#include <algorithm>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/upper_bound.hpp>

using namespace utils::interval;

namespace aoc_2023_5 {

void RangeMap::addSection(
    int64_t const dest, int64_t const src, int64_t const length) noexcept
{
    mSections.emplace(dest, src, length);
}

int64_t RangeMap::convert(int64_t const key) const noexcept
{
    for (auto const& section : mSections) {
        auto const value{section.convert(key)};
        if (value) {
            return *value;
        }
    }
    return key;
}

IntervalSet<int64_t>
RangeMap::convert(Interval<int64_t> const& keyInterval) const noexcept
{
    IntervalSet<int64_t> result;

    if (mSections.empty()) {
        result.add(keyInterval);
        return result;
    }

    // Get the first relevant map section
    RangeMapSection const a{0LL, keyInterval.getMin(), 0} LL;
    auto sectionIt = ranges::upper_bound(mSections, a, std::less{});
    if (sectionIt != mSections.begin()) {
        sectionIt = std::prev(sectionIt);
    }

    int64_t start{keyInterval.getMin()};
    int64_t length{static_cast<int64_t>(keyInterval.size())};
    int64_t mapStart{sectionIt->getSource().getMin()};
    int64_t mapLength{static_cast<int64_t>(sectionIt->getSource().size())};
    while (length > 0LL) {
        if (sectionIt == mSections.end()) {
            // No conversion, no more mappings
            result.add(Interval<int64_t>::createWithSize(start, length));
            length = 0LL;
        } else if (start < mapStart) {
            // No conversion
            // (initial part of the range not covered by a mapping)
            int64_t const actualLength = std::min(length, mapStart - start);
            result.add(Interval<int64_t>::createWithSize(start, actualLength));
            start += actualLength;
            length -= actualLength;
        } else if ((start - mapStart) >= mapLength) {
            // The current mapping is no longer relevant
            ++sectionIt;
            mapStart = sectionIt->getSource().getMin();
            mapLength = static_cast<int64_t>(sectionIt->getSource().size());
        } else {
            // Actual conversion
            int64_t const actualLength = std::min(
                static_cast<int64_t>(
                    Interval<int64_t>::createWithBoundaries(
                        start, sectionIt->getSource().getMax())
                        .size()),
                length);
            result.add(Interval<int64_t>::createWithSize(
                convert(start), actualLength));
            start += actualLength;
            length -= actualLength;
        }
    }

    return result;
}

} // namespace aoc_2023_5
