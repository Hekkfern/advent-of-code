#pragma once

#include <concepts>
#include <ostream>

/**
 * @brief      Defines a type which is a signed integer type of any kind, or a
 *             floating-point type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept NumericType = std::is_arithmetic_v<T> && !std::is_same_v<bool, T>;

/**
 * @brief      Defines a type which is a integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept IntegerType = NumericType<T> && std::integral<T>;

/**
 * @brief      Defines a type which is a unsigned integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept UnsignedIntegerType = NumericType<T> && std::unsigned_integral<T>;

/**
 * @brief      Defines a type which is a signed integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept SignedIntegerType = NumericType<T> && std::signed_integral<T>;

/**
 * @brief
 *
 * @tparam T
 */
template <typename T>
concept Streamable = requires(std::ostream& os, T value) {
    { os << value } -> std::convertible_to<std::ostream&>;
};

/**
 * @brief
 *
 * @tparam DataType
 */
template <typename T>
concept Hashable = requires(T value) {
    { std::hash<T>{}(value) } -> std::convertible_to<std::size_t>;
};
