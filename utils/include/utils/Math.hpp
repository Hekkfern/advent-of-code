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
 * @brief
 *
 * @param m
 * @param n
 *
 * @tparam M
 * @tparam N
 *
 * @return constexpr auto
 */
template <NumericType M, NumericType N>
[[nodiscard]] constexpr auto lcm(M const& m, N const& n)
{
    return std::lcm(m, n);
}
/**
 * @brief
 *
 * @param first
 * @param rest
 *
 * @tparam M
 * @tparam Rest
 *
 * @return constexpr auto
 */
template <NumericType M, NumericType... Rest>
[[nodiscard]] constexpr auto lcm(M const& first, Rest const&... rest)
{
    return std::lcm(first, lcm(rest...));
}

} // namespace utils::math
