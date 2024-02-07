#pragma once

#include "Interval.hpp"
#include <iostream>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <string>
#include <utils/String.hpp>
#include <vector>

namespace utils::interval {

/**
 * @brief      This class describes an interval of non-continuous integer
 *             values.
 *
 * @tparam     T     Type of the values.
 */
template <SignedIntegerType T = int32_t>
class IntervalSet {
public:
    /**
     * @brief      Default constructor
     */
    explicit IntervalSet() noexcept = default;
    /**
     * @brief      Parametrized constructor
     *
     * @note       The intervals are compacted and sorted when this instance is
     *             constructed.
     *
     * @param[in]  intervals  The intervals.
     */
    explicit IntervalSet(std::vector<Interval<T>>&& intervals) noexcept
        : mIntervals{std::move(intervals)}
    {
        reduce();
    }
    /**
     * @brief      Parametrized constructor
     *
     * @note       The intervals are compacted and sorted when this instance is
     *             constructed.
     *
     * @param[in]  intervals  The intervals.
     */
    explicit IntervalSet(std::vector<Interval<T>> const& intervals) noexcept
        : mIntervals{intervals}
    {
        reduce();
    }
    /**
     * @brief      Gets the intervals.
     *
     * @return     The intervals.
     */
    [[nodiscard]] std::vector<Interval<T>> get() const noexcept
    {
        return mIntervals;
    }
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    void add(Interval<T> const& interval) noexcept
    {
        mIntervals.emplace_back(interval);
        reduce();
    }
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    void add(Interval<T>&& interval) noexcept
    {
        mIntervals.emplace_back(std::move(interval));
        reduce();
    }
    /**
     * @brief      Adds the specified value.
     *
     * @param[in]  value  The value to add.
     */
    void add(T const value) noexcept
    {
        mIntervals.emplace_back(value, value);
        reduce();
    }
    /**
     * @brief      Removes the specified value, if it is contained.
     *
     * @param      value  The value to remove.
     */
    void remove(T const value) noexcept
    {
        std::vector<Interval<T>> tempIntervals;
        tempIntervals.reserve(mIntervals.size());
        for (auto const& item : mIntervals) {
            if (item.contains(value)) {
                if (!item.hasOneValue()) {
                    if (item.getMin() == value) {
                        tempIntervals.emplace_back(value + 1, item.getMax());
                    } else if (item.getMax() == value) {
                        tempIntervals.emplace_back(item.getMin(), value - 1);
                    } else {
                        tempIntervals.emplace_back(item.getMin(), value - 1);
                        tempIntervals.emplace_back(value + 1, item.getMax());
                    }
                }
            } else {
                tempIntervals.emplace_back(item);
            }
        }
        mIntervals = tempIntervals;
        reduce();
    }
    /**
     * @brief      Removes the specified interval.
     *
     * @param[in]  eraseInterval  The interval to remove.
     */
    void remove(Interval<T> const& eraseInterval) noexcept
    {
        std::vector<Interval<T>> tempIntervals;
        tempIntervals.reserve(mIntervals.size());
        for (auto const& innerInterval : mIntervals) {
            if (innerInterval.subsumes(eraseInterval)) {
                // this interval is split in half because of the erased value
                tempIntervals.emplace_back(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
                tempIntervals.emplace_back(
                    eraseInterval.getMax() + 1, innerInterval.getMax());
            } else if (
                eraseInterval.getMin() >= innerInterval.getMin()
                && eraseInterval.getMin() <= innerInterval.getMax()) {
                // this interval is not totally subsumed, so it is partially
                // deleted
                tempIntervals.emplace_back(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
            } else if (
                eraseInterval.getMax() >= innerInterval.getMin()
                && eraseInterval.getMax() <= innerInterval.getMax()) {
                // this interval is not totally subsumed so it is partially
                // deleted
                tempIntervals.emplace_back(
                    eraseInterval.getMax() + 1, innerInterval.getMax());
            } else if (!eraseInterval.subsumes(innerInterval)) {
                tempIntervals.emplace_back(innerInterval);
            }
        }
        mIntervals = tempIntervals;
        reduce();
    }
    /**
     * @brief      Merges both intervals.
     *
     * @param[in]  other  The other interval.
     *
     * @return     The result of merging both intervals.
     */
    [[nodiscard]] IntervalSet join(IntervalSet const& other) const noexcept
    {
        std::vector<Interval<T>> joinedIntervals{mIntervals};
        joinedIntervals.reserve(mIntervals.size() + other.mIntervals.size());
        ranges::copy(other.mIntervals, std::back_inserter(joinedIntervals));
        return IntervalSet{joinedIntervals};
    }
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    [[nodiscard]] bool subsumes(IntervalSet const& other) const noexcept
    {
        return ranges::all_of(
            other.mIntervals, [this](Interval<T> const& otherInterval) {
                return subsumes(otherInterval);
            });
    }
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    [[nodiscard]] bool subsumes(Interval<T> const& other) const noexcept
    {
        return ranges::any_of(
            mIntervals, [&other](Interval<T> const& interval) {
                return interval.subsumes(other);
            });
    }
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    [[nodiscard]] bool overlaps(IntervalSet const& other) const noexcept
    {
        return ranges::any_of(
            other.mIntervals, [this](Interval<T> const& otherInterval) {
                return overlaps(otherInterval);
            });
    }
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    [[nodiscard]] bool overlaps(Interval<T> const& other) const noexcept
    {
        return ranges::any_of(
            mIntervals, [&other](Interval<T> const& interval) -> bool {
                return interval.overlaps(other);
            });
    }
    /**
     * @brief      Checks if the specified value is contained in the interval.
     *
     * @param[in]  value  The value to check.
     *
     * @return     True if the interval contains the value. False, otherwise.
     */
    [[nodiscard]] bool contains(T const value) const noexcept
    {
        return ranges::any_of(
            mIntervals, [value](Interval<T> const& interval) -> bool {
                return interval.contains(value);
            });
    }
    /**
     * @brief      Gets the number of contained items.
     *
     * @return     Total number of items.
     */
    [[nodiscard]] size_t count() const noexcept
    {
        return ranges::fold_left(
            mIntervals, 0U, [](size_t const sum, Interval<T> const& interval) {
                return sum + interval.length();
            });
    }
    /**
     * @brief      Extracts a sub @ref IntervalSet contained between the
     *             selected values.
     *
     * @param[in]  min   The minimum value of the range to extract from.
     * @param[in]  max   The maximum value of the range to extract from.
     *
     * @return     A sub interval.
     */
    [[nodiscard]] IntervalSet extract(T min, T max) const noexcept
    {
        IntervalSet resultInterval{mIntervals};
        resultInterval.remove(Interval{std::numeric_limits<T>::min(), min - 1});
        resultInterval.remove(Interval{max + 1, std::numeric_limits<T>::max()});
        return resultInterval;
    }
    /**
     * @brief      Gets the sub @ref Interval that contains the selected value
     *
     * @param[in]  value  The value.
     *
     * @return     The interval containing this value, or std::nullopt.
     */
    [[nodiscard]] std::optional<Interval<T>>
    getIntervalFor(T const value) const noexcept
    {
        auto const it{ranges::find_if(
            mIntervals, [value](Interval<T> const& interval) -> bool {
                return interval.contains(value);
            })};
        if (it == mIntervals.cend()) {
            return {};
        }
        return *it;
    }
    /**
     * @brief      Calculates the overlapping parts of both provided intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     A new @ref IntervalSet with the overlapped fragment.
     */
    [[nodiscard]] constexpr IntervalSet
    intersect(Interval<T> const& other) const noexcept
    {
        std::vector<Interval<T>> overlappedIntervals;
        for (Interval<T> const& internalInterval : mIntervals) {
            auto const result{internalInterval.intersect(other)};
            if (result) {
                overlappedIntervals.emplace_back(*result);
            }
        }
        return IntervalSet{overlappedIntervals};
    }
    /**
     * @brief      Implicit conversion operator to @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const noexcept
    {
        if (mIntervals.empty()) {
            return "[]";
        }
        return ranges::fold_left(
            mIntervals.begin() + 1,
            mIntervals.end(),
            mIntervals[0].toString(),
            [](std::string const& accum, Interval<T> const& item)
                -> std::string { return accum + "," + item.toString(); });
    }
    /**
     * @brief      Checks if there is any interval.
     *
     * @return     True if the interval set is empty. False, otherwise.
     */
    [[nodiscard]] bool empty() const noexcept { return mIntervals.empty(); }
    /**
     * @brief      Equality operator
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(IntervalSet const& other) const
    {
        return mIntervals == other.mIntervals;
    }

private:
    /**
     * @brief      Sorts the list of intervals, and merges contiguous intervals
     *             to try to reduce the total of intervals in the list.
     */
    void reduce() noexcept
    {
        if (mIntervals.empty()) {
            return;
        }
        // order the intervals
        ranges::sort(mIntervals);
        // try to join intervals
        std::vector<Interval<T>> newIntervals{};
        Interval<T> accumulatedInterval{mIntervals[0]};
        for (auto const& item : mIntervals) {
            auto newInterval{accumulatedInterval.join(item)};
            if (!newInterval) {
                newIntervals.emplace_back(accumulatedInterval);
                accumulatedInterval = item;
            } else {
                accumulatedInterval = *newInterval;
            }
        }
        newIntervals.emplace_back(accumulatedInterval);
        mIntervals = newIntervals;
    }
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os           The output stream.
     * @param[in]  intervalSet  The interval.
     *
     * @return     The updated output stream.
     */
    friend std::ostream&
    operator<<(std::ostream& os, IntervalSet const& intervalSet)
    {
        os << intervalSet.toString();
        return os;
    }

    /**
     * List of intervals.
     *
     * @note       No interval is overlapped.
     * @note       All the intervals are sorted by ascending order of its
     *             minimal value.
     * @note       Two contiguous intervals mean that there is a gap in-between
     *             of, at least, one value.
     */
    std::vector<Interval<T>> mIntervals{};
};

} // namespace utils::interval
