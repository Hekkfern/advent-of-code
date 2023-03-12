#include "Interval.hpp"

#include <algorithm>

namespace utils::interval {

Interval::Interval(int32_t min, int32_t max)
    : mMin{ min }
    , mMax{ max }
{
}

uint32_t Interval::length() const { return static_cast<uint32_t>(mMax - mMin); }

Interval Interval::join(const Interval& other) const
{
    return Interval{ std::min(other.mMin, mMin), std::max(other.mMax, mMax) };
}

int32_t Interval::getMin() const { return mMin; }

int32_t Interval::getMax() const { return mMax; }

std::pair<int32_t, int32_t> Interval::get() const
{
    return std::make_pair(mMin, mMax);
}

Interval Interval::operator+(const Interval& other) const
{
    return this->join(other);
}

bool Interval::subsumes(const Interval& other) const
{
    return other.mMin >= mMin && other.mMax <= mMax;
}

bool Interval::overlaps(const Interval& other) const
{
    return (other.mMin >= mMin && other.mMin <= mMax)
        || (other.mMax >= mMin && other.mMax <= mMax) || other.subsumes(*this);
}

} // namespace utils::interval