#pragma once

#include "Interval.hpp"
#include <vector>

namespace utils::interval {

/**
 * @brief      This class describes an interval of non-continuous integer values.
 */
class MultiInterval {
public:
    /**
     * @brief      Default constructor
     */
    MultiInterval() = default;
    /**
     * @brief      Constructs a new instance from some intervals
     *
     * @param[in]  intervals  The intervals.
     */
    explicit MultiInterval(std::vector<Interval>&& intervals);
    /**
     * @brief      Gets the intervals.
     *
     * @return     The intervals.
     */
    const std::vector<Interval>& get() const;
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    void add(const Interval& interval);
    /**
     * @brief      Merges both intervals.
     *
     * @param[in]  other  The other interval.
     *
     * @return     The result of merging both intervals.
     */
    MultiInterval join(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    bool subsumes(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    bool subsumes(const Interval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    bool overlaps(const MultiInterval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    bool overlaps(const Interval& other) const;

private:
    /**
     * @brief      Sorts the list of intervals, and merges contiguos intervals
     *             to try to reduce the total of intervals in the list.
     */
    void reduce();

    /**
     * @brief      List of intervals.
     *
     * @note       No interval is overlapped.
     * @note       All the intervals are sorted by ascending order of its
     *             minimal value.
     * @note       Two contiguous intervals mean that there is a gap between
     *             them of, at least, one value.
     */
    std::vector<Interval> mIntervals{};
};

} // namespace utils::interval
