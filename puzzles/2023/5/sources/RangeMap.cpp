
#include "RangeMap.hpp"

namespace aoc_2023_5 {

RangeMapSection::RangeMapSection(uint32_t dest, uint32_t src, uint32_t length)
    : mDestinationStart{dest}
    , mSourceStart{src}
    , mRangeLength{length}
{
}

std::optional<uint32_t> RangeMapSection::get(uint32_t const key) const noexcept
{
    if (key < mSourceStart || key > (mSourceStart + mRangeLength)) {
        return {};
    }
    return mDestinationStart + (key - mSourceStart);
}

void RangeMap::addSection(
    uint32_t const dest, uint32_t const src, uint32_t const length) noexcept
{
    mSections.emplace_back(dest, src, length);
}

std::optional<uint32_t> RangeMap::get(uint32_t key) const noexcept
{
    std::optional<uint32_t> result;
    for (auto const& section : mSections) {
        auto const value{section.get(key)};
        if (value) {
            return value;
        }
    }
    return result;
}

} // namespace aoc_2023_5