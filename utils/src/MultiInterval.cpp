#include "MultiInterval.hpp"

#include <range/v3/all.hpp>

namespace utils::interval {

MultiInterval::MultiInterval(std::vector<Interval>&& intervals)
    : mIntervals{ std::move(intervals) }
{
    // order the intervals
    std::sort(mIntervals.begin(), mIntervals.end());
}

void MultiInterval::add(const Interval& interval)
{
    // if the interval is already contained, do nothing
    if (subsumes(interval)) {
        return;
    }

    if (overlaps(interval)) {
        for (size_t i{ 0U }; i < mIntervals.size(); ++i) {
            //TODO
        }
    } else {
        mIntervals.emplace_back(interval);
    }

    std::sort(mIntervals.begin(), mIntervals.end());
}


bool MultiInterval::subsumes(const MultiInterval& other) const
{
    return ranges::all_of(
        other.mIntervals, [this](const Interval& otherInterval) {
            return subsumes(otherInterval);
        });
}

bool MultiInterval::subsumes(const Interval& other) const
{
    return ranges::any_of(mIntervals, [&other](const Interval& interval) {
        return interval.subsumes(other);
    });
}

bool MultiInterval::overlaps(const MultiInterval& other) const { 
    return ranges::any_of(
        other.mIntervals, [this](const Interval& otherInterval) {
            return overlaps(otherInterval);
        });
}

bool MultiInterval::overlaps(const Interval& other) const
{
    return ranges::any_of(mIntervals, [&other](const Interval& interval) {
        return interval.overlaps(other);
    });
}

} // namespace utils::interval
