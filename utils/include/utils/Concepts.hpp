#pragma once

#include <concepts>

/**
 * @brief      Defines a type which is a signed integer type of any kind, or a
 *             floating-point type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept NumericType = requires(T param) {
    requires std::integral<T> || std::floating_point<T>;
    requires !std::is_same_v<bool, T>;
    requires std::is_arithmetic_v<decltype(param + 1)>;
    requires !std::is_pointer_v<T>;
};

/**
 * @brief      Defines a type which is a unsigned integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept UnsignedIntegerType = requires(T param) {
    requires std::unsigned_integral<T>;
    requires !std::is_same_v<bool, T>;
    requires std::is_arithmetic_v<decltype(param + 1)>;
    requires !std::is_pointer_v<T>;
};

/**
 * @brief      Defines a type which is a signed integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept SignedIntegerType = requires(T param) {
    requires std::signed_integral<T>;
    requires !std::is_same_v<bool, T>;
    requires std::is_arithmetic_v<decltype(param + 1)>;
    requires !std::is_pointer_v<T>;
};

/**
 * @brief      Defines a type which is a integer type of any kind.
 *
 * @tparam     T     Type to validate the concept against.
 */
template <typename T>
concept IntegerType = requires(T param) {
    requires std::integral<T>;
    requires !std::is_same_v<bool, T>;
    requires std::is_arithmetic_v<decltype(param + 1)>;
    requires !std::is_pointer_v<T>;
};
