#include "RangeMapSection.hpp"

namespace aoc_2023_5 {

RangeMapSection::RangeMapSection(uint64_t dest, uint64_t src, uint64_t length)
    : mDestinationStart{dest}
    , mSourceStart{src}
    , mRangeLength{length}
{
}

std::optional<uint64_t> RangeMapSection::get(uint64_t const key) const noexcept
{
    if (key < mSourceStart || key > (mSourceStart + mRangeLength)) {
        return {};
    }
    return mDestinationStart + (key - mSourceStart);
}

bool RangeMapSection::operator<(RangeMapSection const& other) const
{
    return mSourceStart < other.mSourceStart;
}

} // namespace aoc_2023_5