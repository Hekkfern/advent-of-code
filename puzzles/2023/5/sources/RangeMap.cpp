#include "RangeMap.hpp"

#include <algorithm>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/upper_bound.hpp>

using namespace utils::interval;

namespace aoc_2023_5 {

void RangeMap::addSection(
    int64_t const dest, int64_t const src, int64_t const length) noexcept
{
    mSections.emplace_back(dest, src, length);
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
        return result;
    }

    // Get the first relevant map section
    RangeMapSection const a{0, keyInterval.getMin(), 0};
    auto it = ranges::upper_bound(mSections, a, std::less{});
    if (it != mSections.begin()) {
        it = std::prev(it);
    }

    auto start{keyInterval.getMin()};
    auto length{static_cast<int64_t>(keyInterval.length())};
    auto mapStart{it->getSource().getMin()};
    auto mapLength{static_cast<int64_t>(it->getSource().length())};
    while (length > 0) {
        if (it == mSections.end()) {
            // No conversion, no more mappings
            result.add(Interval<int64_t>::createWithLength(start, length));
            length = 0;
        } else if (start < mapStart) {
            // No conversion
            // (initial part of the range not covered by a mapping)
            int64_t const actualLength = std::min(length, mapStart - start);
            result.add(
                Interval<int64_t>::createWithLength(start, actualLength));
            start += actualLength;
            length -= actualLength;
        } else if ((start - mapStart) >= mapLength) {
            // The current mapping is no longer relevant
            ++it;
            mapStart = it->getSource().getMin();
            mapLength = static_cast<int64_t>(it->getSource().length());
        } else {
            // Actual conversion
            int64_t const actualLength = std::min(
                static_cast<int64_t>(
                    Interval<int64_t>::createWithBounds(
                        start, it->getSource().getMax())
                        .length()),
                length);
            result.add(Interval<int64_t>::createWithLength(
                convert(start), actualLength));
            start += actualLength;
            length -= actualLength;
        }
    }

    return result;
}

void RangeMap::sort() noexcept { ranges::sort(mSections, std::less{}); }

} // namespace aoc_2023_5
