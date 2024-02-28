#pragma once

#include "Concepts.hpp"
#include <numeric>

namespace utils::math {

/**
 * @brief      Calculates the modulus of a division of integer values, even if
 *             one of the operands is negative.
 *
 * @param[in]  dividend  The dividend.
 * @param[in]  divisor   The divisor.
 *
 * @tparam     T         Type of the operands and result.
 *
 * @return     Result of the operation.
 */
template <IntegerType T>
[[nodiscard]] constexpr T modulusFloor(T const dividend, T const divisor)
{
    return (dividend % divisor + divisor) % divisor;
}
/**
 * @brief      Computes the "least common multiple" of the selected integers
 *
 * @param      m     First number.
 * @param      n     Second number.
 *
 * @tparam     M     Type of the first number.
 * @tparam     N     Type of the second number.
 *
 * @return     Result of the operation.
 */
template <NumericType M, NumericType N>
[[nodiscard]] constexpr auto lcm(M const& m, N const& n)
{
    return std::lcm(m, n);
}
/**
 * @brief      Computes the "least common multiple" of the selected integers
 *
 * @param      first  First number.
 * @param      rest   Other numbers.
 *
 * @tparam     M      Type of the first number.
 * @tparam     Rest   Type of the other numbers.
 *
 * @return     Result of the operation.
 */
template <NumericType M, NumericType... Rest>
[[nodiscard]] constexpr auto lcm(M const& first, Rest const&... rest)
{
    return std::lcm(first, lcm(rest...));
}
/**
 * @brief      Computes the "greatest common divisor" of the selected integers
 *
 * @param[in]  m     First number.
 * @param[in]  n     Second number.
 *
 * @tparam     M     Type of the first number.
 * @tparam     N     Type of the second number.
 *
 * @return     Result of the operation.
 */
template <NumericType M, NumericType N>
[[nodiscard]] constexpr auto gcd(M const& m, N const& n)
{
    return std::gcd(m, n);
}
/**
 * @brief      Computes the "greatest common divisor" of the selected integers
 *
 * @param[in]  first  First number.
 * @param[in]  rest   Other numbers.
 *
 * @tparam     M      Type of the first number.
 * @tparam     Rest   Type of the other numbers.
 *
 * @return     Result of the operation.
 */
template <NumericType M, NumericType... Rest>
[[nodiscard]] constexpr auto gcd(M const& first, Rest const&... rest)
{
    return std::gcd(first, gcd(rest...));
}

} // namespace utils::math
