#pragma once

#include "Concepts.hpp"
#include <algorithm>
#include <cstdint>
#include <optional>
#include <utility>

namespace utils::interval {

/**
 * @brief      This class describes an interval of continuous integer values.
 *
 * @tparam     T     Type of the values.
 */
template <SignedIntegerType T = int32_t>
class Interval {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  min   The minimum value.
     * @param[in]  max   The maximum value.
     */
    explicit Interval(T min, T max)
        : mMin{min}
        , mMax{max}
    {
        if (mMin > mMax) {
            throw std::runtime_error(
                "The minimum value must be smaller or equal "
                "than the maximum value.");
        }
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  values  A pair of values (Min, Max).
     */
    explicit Interval(const std::pair<T, T>& values)
        : Interval{values.first, values.second}
    {
    }
    /**
     * @brief      Three-way comparison operator.
     *
     * @param[in]  other  The other object to compare to.
     *
     * @return     The result of the three-way comparison.
     */
    [[nodiscard]] auto operator<=>(const Interval& other) const = default;
    /**
     * @brief      Retrieves the length of the interval, i.e. the difference
     *             between the minimum and maximum values.
     *
     * @return     The length of the interval.
     */
    [[nodiscard]] size_t length() const
    {
        return static_cast<size_t>(mMax - mMin) + 1U;
    }
    /**
     * @brief      Joins both intervals to create a new one with the highest
     *             length.
     *
     * @param[in]  other  The other object.
     *
     * @return     Joined interval if they overlap. std::nullopt, otherwise.
     */
    [[nodiscard]] std::optional<Interval> join(const Interval<T>& other) const
    {
        return (overlaps(other) || areContiguous(other))
            ? std::make_optional<Interval<T>>(
                std::min(other.mMin, mMin), std::max(other.mMax, mMax))
            : std::nullopt;
    }
    /**
     * @brief      Creates an interval which contains the overlapping parts of
     *             both provided intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     std::nullopt if they don't overlap. If so, a new interval
     *             with the overlapped fragment.
     */
    [[nodiscard]] std::optional<Interval> intersect(const Interval& other) const
    {
        if (other.mMin >= mMin && other.mMin <= mMax && other.mMax >= mMax) {
            return Interval{other.mMin, mMax};
        } else if (
            other.mMin <= mMin && other.mMax >= mMin && other.mMax <= mMax) {
            return Interval{mMin, other.mMax};
        } else if (other.subsumes(*this)) {
            return std::make_optional(*this);
        } else if (subsumes(other)) {
            return std::make_optional(other);
        } else {
            return std::nullopt;
        }
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
    [[nodiscard]] bool subsumes(const Interval& other) const
    {
        return other.mMin >= mMin && other.mMax <= mMax;
    }
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    [[nodiscard]] bool overlaps(const Interval& other) const
    {
        return (other.mMin >= mMin && other.mMin <= mMax)
            || (other.mMax >= mMin && other.mMax <= mMax)
            || other.subsumes(*this) || subsumes(other);
    }
    /**
     * @brief      Gets the minimum value of the interval.
     *
     * @return     The minimum value.
     */
    [[nodiscard]] T getMin() const { return mMin; }
    /**
     * @brief      Gets the maximum value of the interval.
     *
     * @return     The maximum value.
     */
    [[nodiscard]] T getMax() const { return mMax; }
    /**
     * @brief      Gets both extreme values of the interval.
     *
     * @return     Pair with both the minimum and the maximum values.
     */
    [[nodiscard]] std::pair<T, T> get() const
    {
        return std::make_pair(mMin, mMax);
    }
    /**
     * @brief      Checks if the specified value is contained in the interval.
     *
     * @param[in]  value  The value to check.
     *
     * @return     True if the interval contains the value. False, otherwise.
     */
    [[nodiscard]] bool contains(T value) const
    {
        return value >= mMin && value <= mMax;
    }
    /**
     * @brief      Checks if the interval has one single value, meaning the
     *             minimum value equals the maximum value.
     *
     * @return     True if the interval has a single value. False, otherwise.
     */
    [[nodiscard]] bool hasOneValue() const { return mMin == mMax; }
    /**
     * @brief      Checks if both intervals are contiguous, meaning that the
     *             difference between the minimum value of one interval and the
     *             maximum of the other interval is one, or vice-versa.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if both intervals are contiguous. False, otherwise.
     */
    [[nodiscard]] bool areContiguous(const Interval& other) const
    {
        return (other.mMin - mMax) == 1 || (mMin - other.mMax) == 1;
    }

private:
    /**
     * @brief      Minimum value.
     */
    T mMin;
    /**
     * @brief      Maximum value.
     */
    T mMax;
};

} // namespace utils::interval
