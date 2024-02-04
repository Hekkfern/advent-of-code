#include "RangeMap.hpp"
#include <range/v3/algorithm/sort.hpp>

namespace aoc_2023_5 {

void RangeMap::addSection(
    uint64_t const dest, uint64_t const src, uint64_t const length) noexcept
{
    mSections.emplace_back(dest, src, length);
}

uint64_t RangeMap::get(uint64_t key) const noexcept
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