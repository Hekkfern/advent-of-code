#pragma once

#include "Interval.hpp"
#include <vector>

namespace utils::interval {

/**
 * @brief      This class describes an interval of non-continuous integer
 *             values.
 */
class MultiInterval {
public:
    /**
     * @brief      Default constructor
     */
    MultiInterval() = default;
    /**
     * @brief      Move constructor
     *
     * @param[in]  intervals  The intervals.
     */
    explicit MultiInterval(std::vector<Interval>&& intervals);
    /**
     * @brief      Copy constructor
     *
     * @param[in]  intervals  The intervals.
     */
    explicit MultiInterval(const std::vector<Interval>& intervals);
    /**
     * @brief      Gets the intervals.
     *
     * @return     The intervals.
     */
    [[nodiscard]] const std::vector<Interval>& get() const;
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    void add(const Interval& interval);
    /**
     * @brief      Adds the specified interval.
     *
     * @param[in]  interval  The interval to add.
     */
    void add(Interval&& interval);
    /**
     * @brief      Adds the specified value.
     *
     * @param[in]  value  The value to add.
     */
    void add(const int32_t value);
    /**
     * @brief      Removes the specified value, if it is contained.
     *
     * @param      value  The value to remove.
     */
    void remove(const int32_t value);
    /**
     * @brief      Removes the specified interval.
     *
     * @param[in]  eraseInterval  The interval to remove.
     */
    void remove(const Interval& eraseInterval);
    /**
     * @brief      Merges both intervals.
     *
     * @param[in]  other  The other interval.
     *
     * @return     The result of merging both intervals.
     */
    [[nodiscard]] MultiInterval join(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    [[nodiscard]] bool subsumes(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    [[nodiscard]] bool subsumes(const Interval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    [[nodiscard]] bool overlaps(const MultiInterval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    [[nodiscard]] bool overlaps(const Interval& other) const;
    /**
     * @brief      Checks if the specified value is contained in the interval.
     *
     * @param[in]  value  The value to check.
     *
     * @return     True if the interval contains the value. False, otherwise.
     */
    [[nodiscard]] bool contains(int32_t value) const;
    /**
     * @brief      Gets the number of contained items.
     *
     * @return     Total number of items.
     */
    [[nodiscard]] uint32_t count() const;
    /**
     * @brief      Extracts a sub interval contained between the selected
     *             values.
     *
     * @param[in]  min   The minimum value of the range to extract from.
     * @param[in]  max   The maximum value of the range to extract from.
     *
     * @return     A sub interval.
     */
    [[nodiscard]] MultiInterval extract(int32_t min, int32_t max) const;

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
