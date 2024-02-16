#include "RangeMap.hpp"

#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/upper_bound.hpp>

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

utils::interval::IntervalSet<int64_t> RangeMap::convert(
    utils::interval::Interval<int64_t> const& keyInterval) const noexcept
{
    utils::interval::IntervalSet<int64_t> result;
    // Get the first relevant map
    RangeMapSection const a{0, keyInterval.getMin(), 1};
    auto it = ranges::upper_bound(mSections, a, std::less{});
    if (it != mSections.cbegin()) {
        it = std::prev(it);
    }

    // TODO

    return result;
}

void RangeMap::sort() noexcept { ranges::sort(mSections, std::less{}); }

} // namespace aoc_2023_5
