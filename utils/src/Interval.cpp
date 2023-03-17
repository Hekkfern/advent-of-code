#include "Interval.hpp"

#include <algorithm>
#include <stdexcept>

namespace utils::interval {

Interval::Interval(int32_t min, int32_t max)
    : mMin{ min }
    , mMax{ max }
{
    if (mMin > mMax) {
        throw std::runtime_error("The minimum value must be smaller or equal "
                                 "than the maximum value.");
    }
}

Interval::Interval(const std::pair<int32_t, int32_t>& values)
    : Interval{ values.first, values.second }
{
}

Interval& Interval::operator=(const Interval& other)
{
    if (this != &other)
        std::construct_at(
            this,
            other); // no destruction needed since trivially destructible
    return *this;
}

uint32_t Interval::length() const { return static_cast<uint32_t>(mMax - mMin); }

std::optional<Interval> Interval::join(const Interval& other) const
{
    return overlaps(other) ? std::make_optional<Interval>(
               std::min(other.mMin, mMin), std::max(other.mMax, mMax))
                           : std::nullopt;
}

int32_t Interval::getMin() const { return mMin; }

int32_t Interval::getMax() const { return mMax; }

std::pair<int32_t, int32_t> Interval::get() const
{
    return std::make_pair(mMin, mMax);
}

bool Interval::contains(const int32_t value) const
{
    return value >= mMin && value <= mMax;
}

std::optional<Interval> Interval::intersect(const Interval& other) const
{
    if (other.mMin >= mMin && other.mMin <= mMax && other.mMax >= mMax) {
        return Interval{ other.mMin, mMax };
    } else if (other.mMin <= mMin && other.mMax >= mMin && other.mMax <= mMax) {
        return Interval{ mMin, other.mMax };
    } else if (other.subsumes(*this)) {
        return std::make_optional(*this);
    } else if (subsumes(other)) {
        return std::make_optional(other);
    } else {
        return std::nullopt;
    }
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
