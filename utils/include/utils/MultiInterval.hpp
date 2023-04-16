#pragma once

#include "Interval.hpp"
#include <range/v3/all.hpp>
#include <vector>

namespace utils::interval {

/**
 * @brief      This class describes an interval of non-continuous integer
 *             values.
 *
 * @tparam     T     Type of the values.
 */
template <SignedIntegerType T = int32_t>
class MultiInterval {
public:
    /**
     * @brief      Default constructor
     */
    constexpr MultiInterval() noexcept = default;
    /**
     * @brief      Move constructor
     *
     * @param[in]  intervals  The intervals.
     */
    constexpr explicit MultiInterval(
        std::vector<Interval<T>>&& intervals) noexcept
        : mIntervals{std::move(intervals)}
    {
        reduce();
    }
    /**
     * @brief      Copy constructor
     *
     * @param[in]  intervals  The intervals.
     */
    constexpr explicit MultiInterval(
        const std::vector<Interval<T>>& intervals) noexcept
        : mIntervals{intervals}
    {
        reduce();
    }
    /**
     * @brief      Gets the intervals.
     *
     * @return     The intervals.
     */
    [[nodiscard]] constexpr const std::vector<Interval<T>>& get() const noexcept
    {
        return mIntervals;
    }
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    constexpr void add(const Interval<T>& interval) noexcept
    {
        mIntervals.emplace_back(interval);
        reduce();
    }
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    constexpr void add(Interval<T>&& interval) noexcept
    {
        mIntervals.emplace_back(std::move(interval));
        reduce();
    }
    /**
     * @brief      Adds the specified value.
     *
     * @param[in]  value  The value to add.
     */
    constexpr void add(const T value) noexcept
    {
        mIntervals.emplace_back(value, value);
        reduce();
    }
    /**
     * @brief      Removes the specified value, if it is contained.
     *
     * @param      value  The value to remove.
     */
    constexpr void remove(const T value) noexcept
    {
        std::vector<Interval<T>> tempIntervals;
        tempIntervals.reserve(mIntervals.size());
        for (const auto& item : mIntervals) {
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
    constexpr void remove(const Interval<T>& eraseInterval) noexcept
    {
        std::vector<Interval<T>> tempIntervals;
        tempIntervals.reserve(mIntervals.size());
        for (const auto& innerInterval : mIntervals) {
            if (innerInterval.subsumes(eraseInterval)) {
                // this interval is split in half because of the erase
                tempIntervals.emplace_back(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
                tempIntervals.emplace_back(
                    eraseInterval.getMax() + 1, innerInterval.getMax());
            } else if (
                eraseInterval.getMin() >= innerInterval.getMin()
                && eraseInterval.getMin() <= innerInterval.getMax()) {
                // this interval is not totally subsumed so it is deleted
                // partially
                tempIntervals.emplace_back(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
            } else if (
                eraseInterval.getMax() >= innerInterval.getMin()
                && eraseInterval.getMax() <= innerInterval.getMax()) {
                // this interval is not totally subsumed so it is deleted
                // partially
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
    [[nodiscard]] constexpr MultiInterval
    join(const MultiInterval& other) const noexcept
    {
        std::vector<Interval<T>> joinedIntervals{mIntervals};
        joinedIntervals.reserve(mIntervals.size() + other.mIntervals.size());
        ranges::copy(other.mIntervals, std::back_inserter(joinedIntervals));
        return MultiInterval{std::move(joinedIntervals)};
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
    [[nodiscard]] constexpr bool
    subsumes(const MultiInterval& other) const noexcept
    {
        return ranges::all_of(
            other.mIntervals, [this](const Interval<T>& otherInterval) {
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
    [[nodiscard]] constexpr bool
    subsumes(const Interval<T>& other) const noexcept
    {
        return ranges::any_of(
            mIntervals, [&other](const Interval<T>& interval) {
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
    [[nodiscard]] constexpr bool
    overlaps(const MultiInterval& other) const noexcept
    {
        return ranges::any_of(
            other.mIntervals, [this](const Interval<T>& otherInterval) {
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
    [[nodiscard]] constexpr bool
    overlaps(const Interval<T>& other) const noexcept
    {
        return ranges::any_of(
            mIntervals, [&other](const Interval<T>& interval) -> bool {
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
    [[nodiscard]] constexpr bool contains(T value) const noexcept
    {
        return ranges::any_of(
            mIntervals, [value](const Interval<T>& interval) -> bool {
                return interval.contains(value);
            });
    }
    /**
     * @brief      Gets the number of contained items.
     *
     * @return     Total number of items.
     */
    [[nodiscard]] constexpr size_t count() const noexcept
    {
        return ranges::accumulate(
            mIntervals, 0U, [](const size_t sum, const Interval<T>& interval) {
                return sum + interval.length();
            });
    }
    /**
     * @brief      Extracts a sub interval contained between the selected
     *             values.
     *
     * @param[in]  min   The minimum value of the range to extract from.
     * @param[in]  max   The maximum value of the range to extract from.
     *
     * @return     A sub interval.
     */
    [[nodiscard]] constexpr MultiInterval extract(T min, T max) const noexcept
    {
        MultiInterval resultInterval{mIntervals};
        resultInterval.remove(Interval{std::numeric_limits<T>::min(), min - 1});
        resultInterval.remove(Interval{max + 1, std::numeric_limits<T>::max()});
        return resultInterval;
    }

private:
    /**
     * @brief      Sorts the list of intervals, and merges contiguous intervals
     *             to try to reduce the total of intervals in the list.
     */
    constexpr void reduce() noexcept
    {
        // order the intervals
        ranges::sort(mIntervals);
        // try to join intervals
        std::vector<Interval<T>> newIntervals{};
        Interval accumulatedInterval{mIntervals[0]};
        for (const auto& item : mIntervals) {
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
     * @brief      List of intervals.
     *
     * @note       No interval is overlapped.
     * @note       All the intervals are sorted by ascending order of its
     *             minimal value.
     * @note       Two contiguous intervals mean that there is a gap between
     *             them of, at least, one value.
     */
    std::vector<Interval<T>> mIntervals{};
};

} // namespace utils::interval
