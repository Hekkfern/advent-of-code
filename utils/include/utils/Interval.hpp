#pragma once

#include "Concepts.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <optional>

namespace utils::interval {

/**
 * @brief      This class describes an interval of continuous integer values,
 *             where both bound values are included in the interval.
 *
 * @tparam     T     Type of the values.
 */
template <SignedIntegerType T = int32_t>
class Interval {
public:
    enum class Location { Less = -1, Within = 0, Greater = 1 };
    enum class Boundary { Start, End };

    /**
     * @brief      Constructs a new instance.
     *
     * @note       Always sets left as min and right as max to simplify
     *             assumptions.
     *
     * @param[in]  a     One boundary.
     * @param[in]  b     Another boundary.
     */
    constexpr explicit Interval(T a, T b)
        : mMin{std::min(a, b)}
        , mMax{std::max(a, b)}
    {
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
     *             different values between the minimum and maximum values (both
     *             included).
     *
     * @return     The length of the interval.
     */
    [[nodiscard]] constexpr std::size_t length() const noexcept
    {
        return static_cast<std::size_t>(mMax - mMin) + 1U;
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
    join(Interval const& other) const noexcept
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
     * @details    For example, intervals [1,2] and [3,4] are contiguous, but
     *             intervals [1,3] and [2,4] aren't.
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
    /**
     * @brief      Checks where the value is relative to the interval.
     *
     * @param[in]  value  Value to compare against the interval
     *
     * @return     Enum with the result.
     */
    Location where(T const value) const
    {
        if (mMax < value) {
            return Location::Greater;
        }
        if (value < mMin) {
            return Location::Less;
        }
        return Location::Within;
    }

    /**
     * @brief      Shifts the interval by the selecter amount of positions.
     *
     * @param[in]  offset  The offset. Positive numbers moves it up, and
     *                     negative numbers moves it down.
     */
    void move(T const offset) const
    {
        mMin += offset;
        mMax += offset;
    }

    /**
     * @brief      Calculates the relative position of the selected value from
     *             the boundary selected in @p boundary parameter.
     *
     * @param[in]  boundary  The boundary to compare to.
     * @param[in]  value     The value to check.
     *
     * @return     The relative position. A positive value means it is higher
     *             that the boundary, and a negative value means it is lower.
     */
    T getRelativePosition(Boundary const boundary, T const value) const
    {
        switch (boundary) {
        case Boundary::Start:
            return value - mMin;
            break;
        case Boundary::End:
            return value - mMax;
            break;
        }
    }

    /**
     * @brief      Creates an interval by setting both boundaries.
     *
     * @param[in]  a     One boundary.
     * @param[in]  b     Another boundary.
     *
     * @tparam     U     Type of the first boundary.
     * @tparam     V     Type of the second boundary.
     *
     * @return     New interval.
     */
    template <class U, class V>
    static Interval createWithBounds(U const a, V const b)
    {
        return Interval{static_cast<T>(a), static_cast<T>(b)};
    }

    /**
     * @brief      Creates an interval by setting one boundary and its length.
     *
     * @param[in]  a     One boundary.
     * @param[in]  l     The length of the interval.
     *
     * @tparam     U     Type of the first boundary (the minimum).
     * @tparam     V     Type of the length of the interval.
     *
     * @return     New interval.
     */
    template <class U, class V>
    static Interval createWithLength(U const a, V const l)
    {
        auto const start{static_cast<T>(a)};
        return Interval{start, start + static_cast<T>(l)};
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os        The output stream.
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
     * Minimum value.
     */
    T mMin;
    /**
     * Maximum value.
     */
    T mMax;
};

} // namespace utils::interval
