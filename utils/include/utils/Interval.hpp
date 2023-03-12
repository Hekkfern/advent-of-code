#pragma once

#include <compare>
#include <cstdint>
#include <utility>

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
    Interval join(const Interval& other) const;
    bool subsumes(const Interval& other) const;
    bool overlaps(const Interval& other) const;
    int32_t getMin() const;
    int32_t getMax() const;
    std::pair<int32_t, int32_t> get() const;

private:
    int32_t mMin;
    int32_t mMax;
};

} // namespace utils::interval