#pragma once

#include "Interval.hpp"
#include <ostream>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <set>
#include <string>
#include <utils/String.hpp>
#include <vector>

namespace utils::interval {

/**
 * @brief      Represents a set of non-overlapping intervals.
 * @details    This class provides operations to add and remove intervals or
 *             individual values, automatically merging overlapping intervals to
 *             maintain a set of non-overlapping intervals.
 *
 * @tparam     T     The type of the interval boundaries, must satisfy
 *                   SignedIntegerType concept.
 */
template <SignedIntegerType T = int32_t>
class IntervalSet {
public:
    /**
     * @brief      Default constructor. Initializes an empty IntervalSet.
     */
    explicit IntervalSet() noexcept = default;
    /**
     * @brief      Constructs an IntervalSet from a set of intervals.
     *             Overlapping intervals are merged.
     *
     * @param[in]  intervals  A set of intervals to initialize the IntervalSet.
     *
     * @{
     */
    explicit IntervalSet(std::set<Interval<T>> const& intervals) noexcept
        : mIntervals{intervals}
    {
        reduce();
    }
    explicit IntervalSet(std::set<Interval<T>>&& intervals) noexcept
        : mIntervals{std::move(intervals)}
    {
        reduce();
    }
    /** }@ */
    /**
     * @brief      Constructs an IntervalSet from a vector of intervals, merging
     *             overlaps.
     *
     * @param[in]  intervals  A vector of intervals to initialize the
     *                        IntervalSet.
     *
     * @{
     */
    explicit IntervalSet(std::vector<Interval<T>> const& intervals) noexcept
        : mIntervals{
              std::set<Interval<T>>{intervals.cbegin(), intervals.cend()}}
    {
        reduce();
    }
    explicit IntervalSet(std::vector<Interval<T>>&& intervals) noexcept
        : mIntervals{
              std::set<Interval<T>>{intervals.cbegin(), intervals.cend()}}
    {
        reduce();
    }
    /** }@ */
    /**
     * @brief      Gets the intervals.
     *
     * @return     The intervals.
     */
    [[nodiscard]] std::vector<Interval<T>> get() const noexcept
    {
        return std::vector<Interval<T>>{mIntervals.cbegin(), mIntervals.cend()};
    }
    /**
     * @brief      Adds an interval, merging it with any overlapping intervals.
     *
     * @param[in]  interval  The interval to add.
     *
     * @{
     */
    void add(Interval<T> const& interval) noexcept
    {
        mIntervals.emplace(interval);
        reduce();
    }
    void add(Interval<T>&& interval) noexcept
    {
        mIntervals.emplace(std::move(interval));
        reduce();
    }
    /** }@ */
    /**
     * @brief      Adds a new interval defined by a single value.
     *
     * @details    This is equivalent to adding an interval where both
     *             boundaries are this value.
     *
     * @param[in]  value  The value to add as a single-value interval.
     */
    void add(T const value) noexcept
    {
        mIntervals.emplace(value, value);
        reduce();
    }
    /**
     * @brief      Removes a specific value, splitting intervals as necessary.
     *
     * @param[in]  value  The value to remove.
     */
    void remove(T const value) noexcept
    {
        std::set<Interval<T>> tempIntervals;
        for (auto const& item : mIntervals) {
            if (item.contains(value)) {
                if (!item.hasOneValue()) {
                    if (item.getMin() == value) {
                        tempIntervals.emplace(value + 1, item.getMax());
                    } else if (item.getMax() == value) {
                        tempIntervals.emplace(item.getMin(), value - 1);
                    } else {
                        tempIntervals.emplace(item.getMin(), value - 1);
                        tempIntervals.emplace(value + 1, item.getMax());
                    }
                }
            } else {
                tempIntervals.emplace(item);
            }
        }
        mIntervals = tempIntervals;
        reduce();
    }
    /**
     * @brief      Removes an interval, adjusting or splitting intervals as
     *             needed.
     *
     * @param[in]  eraseInterval  The interval to remove.
     */
    void remove(Interval<T> const& eraseInterval) noexcept
    {
        std::set<Interval<T>> tempIntervals;
        for (auto const& innerInterval : mIntervals) {
            if (innerInterval.subsumes(eraseInterval)) {
                // this interval is split in half because of the erased value
                tempIntervals.emplace(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
                tempIntervals.emplace(
                    eraseInterval.getMax() + 1, innerInterval.getMax());
            } else if (
                eraseInterval.getMin() >= innerInterval.getMin()
                && eraseInterval.getMin() <= innerInterval.getMax()) {
                // this interval is not totally subsumed, so it is partially
                // deleted
                tempIntervals.emplace(
                    innerInterval.getMin(), eraseInterval.getMin() - 1);
            } else if (
                eraseInterval.getMax() >= innerInterval.getMin()
                && eraseInterval.getMax() <= innerInterval.getMax()) {
                // this interval is not totally subsumed so it is partially
                // deleted
                tempIntervals.emplace(
                    eraseInterval.getMax() + 1, innerInterval.getMax());
            } else if (!eraseInterval.subsumes(innerInterval)) {
                tempIntervals.emplace(innerInterval);
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
        std::set<Interval<T>> joinedIntervals{mIntervals};
        for (auto const& item : other.mIntervals) {
            joinedIntervals.emplace(item);
        }
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
        std::set<Interval<T>> overlappedIntervals;
        for (Interval<T> const& internalInterval : mIntervals) {
            auto const result{internalInterval.intersect(other)};
            if (result) {
                overlappedIntervals.emplace(*result);
            }
        }
        return IntervalSet{overlappedIntervals};
    }
    /**
     * @brief      Represents this class as a @ref std::string.
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const noexcept
    {
        if (mIntervals.empty()) {
            return "";
        }
        auto const intervalsStr
            = mIntervals
            | ranges::views::
                transform([](Interval<T> const& item) -> std::string {
                    return item.toString();
                })
            | ranges::to<std::vector>;
        return utils::string::join(intervalsStr, ",");
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

    auto begin() { return mIntervals.begin(); }
    auto end() { return mIntervals.end(); }
    auto cbegin() const { return mIntervals.cbegin(); }
    auto cend() const { return mIntervals.cend(); }
    auto begin() const { return mIntervals.begin(); }
    auto end() const { return mIntervals.end(); }

private:
    /**
     * @brief      Merges overlapping intervals within the set to maintain the
     *             non-overlapping invariant.
     */
    void reduce() noexcept
    {
        if (mIntervals.empty())
            return; // Early return if there are no intervals to reduce

        // Temporary container for merged intervals
        std::vector<Interval<T>> mergedIntervals;

        // Initialize the process with the first interval in the set
        auto currentInterval = *mIntervals.begin();

        // Iterate through the set starting from the second interval
        for (auto it = std::next(mIntervals.begin()); it != mIntervals.end();
             ++it) {
            // Check if the current interval overlaps with or is adjacent to the
            // next one
            if (currentInterval.getMax() >= it->getMin() - 1) {
                // Merge the current interval with the next one
                currentInterval = Interval<T>(
                    currentInterval.getMin(),
                    std::max(currentInterval.getMax(), it->getMax()));
            } else {
                // If they don't overlap, save the current interval and update
                // it to the next one
                mergedIntervals.push_back(currentInterval);
                currentInterval = *it;
            }
        }
        // Add the last interval to the merged list
        mergedIntervals.push_back(currentInterval);

        // Rebuild the set from the merged intervals
        mIntervals = std::set<Interval<T>>(
            mergedIntervals.begin(), mergedIntervals.end());
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
     * Stores intervals, ensuring no overlaps and sorted order.
     */
    std::set<Interval<T>> mIntervals{};
};

} // namespace utils::interval
