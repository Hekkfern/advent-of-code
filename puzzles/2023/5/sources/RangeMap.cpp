#include "RangeMap.hpp"
#include <range/v3/algorithm/sort.hpp>

namespace aoc_2023_5 {

void RangeMap::addSection(
    int64_t const dest, int64_t const src, int64_t const length) noexcept
{
    mSections.emplace_back(dest, src, length);
}

int64_t RangeMap::get(int64_t const key) const noexcept
{
    for (auto const& section : mSections) {
        auto const value{section.get(key)};
        if (value) {
            return *value;
        }
    }
    return key;
}

void RangeMap::sort() noexcept { ranges::sort(mSections, std::less<>{}); }

} // namespace aoc_2023_5
