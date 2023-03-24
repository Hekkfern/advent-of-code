#include "MultiInterval.hpp"

#include <cassert>
#include <range/v3/all.hpp>

namespace utils::interval {

MultiInterval::MultiInterval(std::vector<Interval>&& intervals)
    : mIntervals{ std::move(intervals) }
{
    reduce();
}

MultiInterval::MultiInterval(const std::vector<Interval>& intervals)
    : mIntervals{ intervals }
{
    reduce();
}

const std::vector<Interval>& MultiInterval::get() const { return mIntervals; }

void MultiInterval::add(const Interval& interval)
{
    mIntervals.emplace_back(interval);
    reduce();
}

void MultiInterval::add(Interval&& interval)
{
    mIntervals.emplace_back(std::move(interval));
    reduce();
}

void MultiInterval::add(const int32_t value)
{
    mIntervals.emplace_back(value, value);
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
    return ranges::any_of(
        mIntervals, [&other](const Interval& interval) -> bool {
            return interval.overlaps(other);
        });
}

MultiInterval MultiInterval::extract(const int32_t min, const int32_t max) const
{
    MultiInterval resultInterval{ mIntervals };
    resultInterval.remove(
        Interval{ std::numeric_limits<int32_t>::min(), min - 1 });
    resultInterval.remove(
        Interval{ max + 1, std::numeric_limits<int32_t>::max() });
    return resultInterval;
}

void MultiInterval::reduce()
{
    // order the intervals
    ranges::sort(mIntervals);
    // try to join intervals
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
    assert(!newIntervals.empty());
    mIntervals = newIntervals;
}

bool MultiInterval::contains(int32_t value) const
{
    return ranges::any_of(
        mIntervals, [value](const Interval& interval) -> bool {
            return interval.contains(value);
        });
}

void MultiInterval::remove(const int32_t value)
{
    for (size_t i{ 0U }; i < mIntervals.size(); ++i) {
        if (mIntervals[i].contains(value)) {
            if (!mIntervals[i].hasOneValue()) {
                if (mIntervals[i].getMin() == value) {
                    mIntervals.emplace_back(value + 1, mIntervals[i].getMax());
                } else if (mIntervals[i].getMax() == value) {
                    mIntervals.emplace_back(mIntervals[i].getMin(), value - 1);
                } else {
                    mIntervals.emplace_back(mIntervals[i].getMin(), value - 1);
                    mIntervals.emplace_back(value + 1, mIntervals[i].getMax());
                }
            }
            mIntervals.erase(std::begin(mIntervals) + static_cast<int64_t>(i));
            reduce();
            break;
        }
    }
}

void MultiInterval::remove(const Interval& eraseInterval)
{
    std::vector<Interval> tempIntervals;
    tempIntervals.reserve(mIntervals.size());
    for (const auto& innerInterval : mIntervals) {
        if (innerInterval.getMin() > eraseInterval.getMax()) {
            break;
        }
        if (innerInterval.subsumes(eraseInterval)) {
            // this interval is split in half because of the erase
            tempIntervals.emplace_back(
                innerInterval.getMin(), eraseInterval.getMin() - 1);
            tempIntervals.emplace_back(
                eraseInterval.getMax() + 1, innerInterval.getMax());
        } else if (
            eraseInterval.getMin() >= innerInterval.getMin()
            && eraseInterval.getMin() <= innerInterval.getMax()) {
            // this interval is not totally subsumed so it is deleted partially
            tempIntervals.emplace_back(
                innerInterval.getMin(), eraseInterval.getMin() - 1);
        } else if (
            eraseInterval.getMax() >= innerInterval.getMin()
            && eraseInterval.getMax() <= innerInterval.getMax()) {
            // this interval is not totally subsumed so it is deleted partially
            tempIntervals.emplace_back(
                eraseInterval.getMax() + 1, innerInterval.getMax());
        }
    }
    mIntervals = tempIntervals;
    reduce();
}

uint32_t MultiInterval::count() const
{
    return ranges::accumulate(
        mIntervals,
        0U,
        [](const uint32_t sum, const utils::interval::Interval& interval) {
            return sum + interval.length();
        });
}

} // namespace utils::interval
