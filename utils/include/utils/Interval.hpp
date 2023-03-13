#pragma once

#include <compare>
#include <cstdint>
#include <utility>
#include <optional>

namespace utils::interval {

class Interval {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  min   The minimum value.
     * @param[in]  max   The maximum value.
     */
    Interval(int32_t min, int32_t max);
    /**
     * @brief      Three-way comparison operator.
     *
     * @param[in]  other  The other object to compare to.
     *
     * @return     The result of the three-way comparison.
     */
    auto operator<=>(const Interval& other) const = default;
    /**
     * @brief      Retrieves the length of the interval, i.e, the difference
     *             between the minimum and maximum values.
     *
     * @return     The length of the interval.
     */
    uint32_t length() const;
    /**
     * @brief      Addition operator which joins both intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     An interval which joins both original intervals.
     */
    Interval operator+(const Interval& other) const;
    /**
     * @brief      Joins both intervals to create a new one with the highest
     *             length.
     *
     * @param[in]  other  The other object.
     *
     * @return     Joined interval.
     */
    Interval join(const Interval& other) const;
    /**
     * @brief      Creates an interval which contains the overlaping parts of
     *             both provided intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     std::nullopt if they don't overlap. If so, a new interval
     *             with the overlapped fragment.
     */
    std::optional<Interval> intersect(const Interval& other) const;
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
    bool overlaps(const Interval& other) const;
    /**
     * @brief      Gets the minimum value of the interval.
     *
     * @return     The minimum value.
     */
    int32_t getMin() const;
    /**
     * @brief      Gets the maximum value of the interval.
     *
     * @return     The maximum value.
     */
    int32_t getMax() const;
    /**
     * @brief      Gets both extreme values of the interval.
     *
     * @return     Pair with both the minimum and the maximum values.
     */
    std::pair<int32_t, int32_t> get() const;

private:
    /**
     * @brief      Minimum value.
     */
    const int32_t mMin;
    /**
     * @brief      Maximum value.
     */
    const int32_t mMax;
};

} // namespace utils::interval
