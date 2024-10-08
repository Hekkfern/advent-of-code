#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <optional>
#include <ostream>
#include <range/v3/algorithm/sort.hpp>
#include <string>
#include <utils/Concepts.hpp>
#include <vector>

namespace utils::interval {

enum class Location { Less, Within, Greater };
enum class Boundary { Start, End };
enum class Relationship { Subsumed, Overlapped, Isolated };

/**
 * @brief      This class describes an interval of continuous integer values,
 *             where both bound values are included in the interval.
 *
 * @tparam     T     Type of the values.
 */
template <SignedIntegerType T = int32_t>
class Interval {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @note       Always sets left as min and right as max to simplify
     *             assumptions.
     *
     * @param[in]  a     One boundary.
     * @param[in]  b     Another boundary.
     */
    constexpr explicit Interval(T const a, T const b)
        : mMin{std::min(a, b)}
        , mMax{std::max(a, b)}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  values  A pair of values (Min, Max).
     *
     * @{
     */
    constexpr explicit Interval(std::pair<T, T> const& values)
        : Interval{values.first, values.second}
    {
    }
    constexpr explicit Interval(std::pair<T, T>&& values)
        : Interval{values.first, values.second}
    {
    }
    /** @} */
    /**
     * @brief      Three-way comparison operator.
     *
     * @param[in]  other  The other object to compare to.
     *
     * @return     The result of the three-way comparison.
     */
    [[nodiscard]] constexpr auto
    operator<=>(Interval const& other) const noexcept
        = default;
    /**
     * @brief      Retrieves the length/size of the interval, i.e. the number of
     *             different values between the minimum and maximum values (both
     *             included).
     *
     * @return     The length of the interval.
     */
    [[nodiscard]] constexpr std::size_t size() const noexcept
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
     * @brief      Creates an interval containing the overlapping parts of both
     *             provided intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     std::nullopt if they don't overlap. Otherwise, a new interval
     *             with the overlapped fragment.
     *
     * @note       It is the opposite of @ref difference method.
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
            return *this;
        } else if (subsumes(other)) {
            return other;
        }
        return {};
    }
    /**
     * @brief      Creates an interval containing the non-common parts of both
     *             provided intervals.
     *
     * @param[in]  other  The other object.
     *
     * @return     std::nullopt if they are equal. Otherwise, a list of
     *             intervals with the non-common parts.
     *
     * @note       It is the opposite of @ref intersect method.
     */
    [[nodiscard]] std::vector<Interval>
    difference(Interval const& other) const noexcept
    {
        std::vector<Interval> results;
        if (mMin < other.mMin && other.mMin <= mMax && mMax < other.mMax) {
            results.emplace_back(mMin, other.mMin - 1);
            results.emplace_back(mMax + 1, other.mMax);
        } else if (
            other.mMin < mMin && mMin <= other.mMax && other.mMax < mMax) {
            results.emplace_back(other.mMin, mMin - 1);
            results.emplace_back(other.mMax + 1, mMax);
        } else if (mMin == other.mMin) {
            if (mMax < other.mMax) {
                results.emplace_back(mMax + 1, other.mMax);
            } else if (other.mMax < mMax) {
                results.emplace_back(other.mMax + 1, mMax);
            }
        } else if (mMax == other.mMax) {
            if (mMin < other.mMin) {
                results.emplace_back(mMin, other.mMin - 1);
            } else if (other.mMin < mMin) {
                results.emplace_back(other.mMin, mMin - 1);
            }
        } else if (other.subsumes(*this)) {
            results.emplace_back(other.mMin, mMin - 1);
            results.emplace_back(mMax + 1, other.mMax);
        } else if (subsumes(other)) {
            results.emplace_back(mMin, other.mMin - 1);
            results.emplace_back(other.mMax + 1, mMax);
        } else {
            results.emplace_back(*this);
            results.emplace_back(other);
        }
        ranges::sort(results);
        return results;
    }
    /**
     * @brief      Checks if this interval includes completely the range of
     *             another one.
     *
     * @details    For example, [0,10] subsumes [2,4].
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    [[nodiscard]] constexpr bool subsumes(Interval const& other) const noexcept
    {
        return mMin <= other.mMin && other.mMax <= mMax;
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
    [[nodiscard]] constexpr std::pair<T, T> getBoundaries() const noexcept
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
    [[nodiscard]] constexpr bool contains(T const value) const noexcept
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
    [[nodiscard]] constexpr Location where(T const value) const noexcept
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
     * @brief      Calculates the relationship with another interval.
     *
     * @param[in]  other  The other object.
     *
     * @return     Enum describing the relationship between both instances.
     */
    [[nodiscard]] constexpr Relationship
    relates(Interval const& other) const noexcept
    {
        if (subsumes(other)) {
            return Relationship::Subsumed;
        } else if (overlaps(other)) {
            return Relationship::Overlapped;
        } else {
            return Relationship::Isolated;
        }
    }
    /**
     * @brief      Shifts the interval by the selected amount of positions, in a
     *             single direction.
     *
     * @param[in]  offset  The offset. Positive numbers moves it up, and
     *                     negative numbers moves it down.
     */
    [[nodiscard]] constexpr Interval move(int64_t const offset) const noexcept
    {
        Interval result{*this};
        result.mMin += static_cast<T>(offset);
        result.mMax += static_cast<T>(offset);
        return result;
    }
    /**
     * @brief      Increases both boundaries by the value in @p offset.
     *
     * @param[in]  offset  Amount to expand. It cannot be a negative number.
     *
     * @return     New expanded interval.
     */
    [[nodiscard]] constexpr Interval
    expand(std::size_t const offset) const noexcept
    {
        Interval result{*this};
        result.mMin -= static_cast<T>(offset);
        result.mMax += static_cast<T>(offset);
        return result;
    }
    /**
     * @brief      Increases both boundaries by the value in @p offset.
     *
     * @param[in]  leftOffset   Amount to expand down. It cannot be a negative
     *                          number.
     * @param[in]  rightOffset  Amount to expand up. It cannot be a negative
     *                          number.
     *
     * @return     New expanded interval.
     */
    [[nodiscard]] constexpr Interval
    expand(std::size_t const leftOffset, std::size_t const rightOffset) const
    {
        Interval result{*this};
        result.mMin -= static_cast<T>(leftOffset);
        result.mMax += static_cast<T>(rightOffset);
        return result;
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
    [[nodiscard]] constexpr T
    getRelativePosition(Boundary const boundary, T const value) const
    {
        switch (boundary) {
        case Boundary::Start:
            return value - mMin;
            break;
        case Boundary::End:
            return value - mMax;
            break;
        }
        return T{0};
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
    [[nodiscard]] constexpr static Interval
    createWithBoundaries(U const a, V const b)
    {
        return Interval{static_cast<T>(a), static_cast<T>(b)};
    }
    /**
     * @brief      Creates an interval by setting one boundary and its length.
     *
     * @param[in]  a     One boundary.
     * @param[in]  l     The length of the interval, including the starting
     * number.
     *
     * @tparam     U     Type of the first boundary (the minimum).
     * @tparam     V     Type of the length of the interval.
     *
     * @return     New interval.
     */
    template <class U, class V>
    [[nodiscard]] constexpr static Interval createWithSize(U const a, V const l)
    {
        auto const start{static_cast<T>(a)};
        return Interval{start, start + static_cast<T>(l) - 1};
    }
    /**
     * @brief      Creates the widest possible interval for type T.
     *
     * @return     New interval.
     */
    [[nodiscard]] constexpr static Interval<T> createWhole()
    {
        return Interval{
            std::numeric_limits<T>::min(), std::numeric_limits<T>::max()};
    }
    /**
     * @brief      Represents this class as a @ref std::string.
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
    {
        // Estimate: Up to 20 chars for 64-bit int, 2 for brackets, 1 for comma
        constexpr size_t estimateSize = 20 + 20 + 2 + 1;
        std::string result;
        result.reserve(estimateSize); // Pre-allocate memory

        result += '[';
        result += std::to_string(mMin);
        result += ',';
        result += std::to_string(mMax);
        result += ']';

        return result;
    }
    /**
     * @brief      Getter for structured binding
     *
     * @tparam     N     Number of tuple-like parameters.
     *
     * @return     The value of the internal variable, according to @p N.
     */
    template <std::size_t N>
    [[nodiscard]] decltype(auto) get() const
    {
        if constexpr (N == 0) {
            return mMin;
        } else if constexpr (N == 1) {
            return mMax;
        }
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os    The output stream.
     * @param[in]  obj   The instance.
     *
     * @return     The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Interval<T> const& obj)
    {
        os << obj.toString();
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

namespace std {

/* Support for structured binding */
template <class T>
struct tuple_size<utils::interval::Interval<T>>
    : std::integral_constant<std::size_t, 2> { };
/* Support for structured binding */
template <class T>
struct tuple_element<0, utils::interval::Interval<T>> {
    using type = T;
};
/* Support for structured binding */
template <class T>
struct tuple_element<1, utils::interval::Interval<T>> {
    using type = T;
};

} // namespace std

template <SignedIntegerType T>
struct std::hash<utils::interval::Interval<T>> {
    std::size_t
    operator()(utils::interval::Interval<T> const& item) const noexcept
    {
        // A prime number for hash combination
        static constexpr std::size_t prime = 31;
        std::size_t const hash1 = std::hash<T>()(item.getMin());
        std::size_t const hash2 = std::hash<T>()(item.getMax());

        // Combine hashes with a prime number and bitwise operations
        std::size_t combinedHash = hash1
            ^ (hash2 * prime + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        return combinedHash;
    }
};
