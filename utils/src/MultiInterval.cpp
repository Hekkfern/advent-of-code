#include "MultiInterval.hpp"

#include <cassert>
#include <range/v3/all.hpp>

namespace utils::interval {

MultiInterval::MultiInterval(std::vector<Interval>&& intervals)
    : mIntervals{ std::move(intervals) }
{
    // order the intervals
    ranges::sort(mIntervals);
    // try to join intervals
    reduce();
}

const std::vector<Interval>& MultiInterval::get() const { return mIntervals; }

void MultiInterval::add(const Interval& interval)
{
    // if the interval is already contained, do nothing
    if (subsumes(interval)) {
        return;
    }

    mIntervals.emplace_back(interval);
    ranges::sort(mIntervals);
    reduce();
}

MultiInterval MultiInterval::join(const MultiInterval& other) const
{
    std::vector<Interval> joinedIntervals{ mIntervals };
    joinedIntervals.reserve(mIntervals.size() + other.mIntervals.size());
    ranges::copy(other.mIntervals, std::back_inserter(joinedIntervals));
    return MultiInterval{ std::move(joinedIntervals) };
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

bool MultiInterval::overlaps(const MultiInterval& other) const
{
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

void MultiInterval::reduce()
{
    std::vector<Interval> newIntervals{};
    Interval accumulatedInterval{ mIntervals[0] };
    for (size_t i{ 1U }; i < mIntervals.size(); ++i) {
        auto newInterval{ accumulatedInterval.join(mIntervals[i]) };
        if (!newInterval) {
            newIntervals.emplace_back(accumulatedInterval);
            accumulatedInterval = mIntervals[i];
        } else {
            accumulatedInterval = *newInterval;
        }
    }
    newIntervals.emplace_back(accumulatedInterval);
    assert(newIntervals.size() >= 1U);
    mIntervals = newIntervals;
}

} // namespace utils::interval
