#include "RangeMapSection.hpp"

namespace aoc_2023_5 {

RangeMapSection::RangeMapSection(
    int64_t const dest, int64_t const src, int64_t const length)
    : mDestination{utils::interval::Interval<int64_t>::createWithLength(
          dest, length)}
    , mSource{utils::interval::Interval<int64_t>::createWithLength(src, length)}
{
}

std::optional<int64_t> RangeMapSection::get(int64_t const key) const noexcept
{
    if (!mSource.contains(key)) {
        return {};
    }
    return mDestination.getMin() + (key - mSource.getMin());
}

bool RangeMapSection::operator<(RangeMapSection const& other) const
{
    return mSource < other.mSource;
}

} // namespace aoc_2023_5
