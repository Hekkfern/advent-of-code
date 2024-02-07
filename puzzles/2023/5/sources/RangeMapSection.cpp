#include "RangeMapSection.hpp"

namespace aoc_2023_5 {

RangeMapSection::RangeMapSection(
    int64_t const dest, int64_t const src, int64_t const length) noexcept
    : mDestination{utils::interval::Interval<int64_t>::createWithLength(
          dest, length)}
    , mSource{utils::interval::Interval<int64_t>::createWithLength(src, length)}
{
}

std::optional<int64_t>
RangeMapSection::convert(int64_t const key) const noexcept
{
    if (!mSource.contains(key)) {
        return {};
    }
    return mDestination.getMin() + (key - mSource.getMin());
}

std::optional<utils::interval::Interval<int64_t>> RangeMapSection::convert(
    utils::interval::Interval<int64_t> const& keyInterval) const noexcept
{
    auto const intersectedSource{keyInterval.intersect(mSource)};
    if (!intersectedSource) {
        return {};
    }
    return utils::interval::Interval<int64_t>{
        *convert(intersectedSource->getMin()),
        *convert(intersectedSource->getMax())};
}

bool RangeMapSection::operator<(RangeMapSection const& other) const noexcept
{
    return mSource < other.mSource;
}

} // namespace aoc_2023_5
