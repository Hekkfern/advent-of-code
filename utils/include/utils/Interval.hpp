#pragma once

#include "Concepts.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <optional>

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
    constexpr explicit Interval(T min, T max)
        : mMin{min}
        , mMax{max}
    {
        assert(
            mMin <= mMax
            && "The minimum value must be smaller or equal than the maximum value");
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  values  A pair of values (Min, Max).
     */
    constexpr explicit Interval(std::pair<T, T> const& values)
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
    [[nodiscard]] auto operator<=>(Interval const& other) const noexcept
        = default;
    /**
     * @brief      Retrieves the length of the interval, i.e. the number of
     * different values between the minimum and maximum values (both included).
     *
     * @return     The length of the interval.
     */
    [[nodiscard]] constexpr size_t length() const noexcept
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
    [[nodiscard]] constexpr std::optional<Interval>
    join(Interval<T> const& other) const noexcept
    {
        return overlaps(other) || areContiguous(other)
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
    [[nodiscard]] constexpr std::optional<Interval>
    intersect(Interval const& other) const noexcept
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
            return {};
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
    [[nodiscard]] constexpr bool subsumes(Interval const& other) const noexcept
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
    [[nodiscard]] constexpr bool overlaps(Interval const& other) const noexcept
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
    [[nodiscard]] constexpr T getMin() const noexcept { return mMin; }
    /**
     * @brief      Gets the maximum value of the interval.
     *
     * @return     The maximum value.
     */
    [[nodiscard]] constexpr T getMax() const noexcept { return mMax; }
    /**
     * @brief      Gets both extreme values of the interval.
     *
     * @return     Pair with both the minimum and the maximum values.
     */
    [[nodiscard]] constexpr std::pair<T, T> get() const noexcept
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
    [[nodiscard]] constexpr bool contains(T value) const noexcept
    {
        return value >= mMin && value <= mMax;
    }
    /**
     * @brief      Checks if the interval has one single value, meaning the
     *             minimum value equals the maximum value.
     *
     * @return     True if the interval has a single value. False, otherwise.
     */
    [[nodiscard]] constexpr bool hasOneValue() const noexcept
    {
        return mMin == mMax;
    }
    /**
     * @brief      Checks if both intervals are contiguous, meaning that the
     *             difference between the minimum value of one interval and the
     *             maximum of the other interval is one, or vice-versa.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if both intervals are contiguous. False, otherwise.
     */
    [[nodiscard]] constexpr bool
    areContiguous(Interval const& other) const noexcept
    {
        return other.mMin - mMax == 1 || mMin - other.mMax == 1;
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]      os       The output stream.
     * @param[in]  interval  The interval.
     *
     * @return     The updated output stream.
     */
    friend std::ostream&
    operator<<(std::ostream& os, Interval<T> const& interval)
    {
        os << '[' << interval.mMin << ',' << interval.mMax << ']';
        return os;
    }

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
