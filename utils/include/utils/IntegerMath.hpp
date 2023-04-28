#pragma once

#include "Concepts.hpp"

namespace utils::integermath {

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

} // namespace utils::integermath
