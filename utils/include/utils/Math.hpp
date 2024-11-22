#pragma once

#include "Concepts.hpp"
#include <numeric>
#include <span>
#include <vector>

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
 * @param[in]  m     First number.
 * @param[in]  n     Second number.
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
 * @param[in]  first  First number.
 * @param[in]  rest   Other numbers.
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
/**
 * @brief      Applies "Lagrange Polynomial"
 *             (https://en.wikipedia.org/wiki/Lagrange_polynomial) technique to
 *             get the coefficients of the lowest degree polynomial that
 *             interpolates the given set of points.
 *
 * @param[in]  coords  The coordinates to use. It CANNOT contain duplicated
 *                     points.
 *
 * @return     Coefficients of the resulting polynomial, ordered from lowest to
 *             highest degree.
 */
[[nodiscard]] std::vector<double> getLowestDegreePolynomial(
    std::vector<std::pair<double, double>> const& coords) noexcept;
/**
 * @brief      Checks if addition will overflow.
 *
 * @param[in]  a     First operand.
 * @param[in]  b     Second operand.
 *
 * @tparam     T     Numeric types of the operands.
 *
 * @return     True if the addition operation will overflow. False otherwise.
 */
template <NumericType T>
[[nodiscard]] bool willAdditionOverflow(T a, T b)
{
    return b > std::numeric_limits<T>::max() - a;
}
/**
 * brief Checks if multiplication will overflow
 *
 * @param[in]  a     First operand.
 * @param[in]  b     Second operand.
 *
 * @tparam     T     Numeric types of the operands.
 *
 * @return     True if the multiplication operation will overflow. False otherwise.
 */
template <NumericType T>
[[nodiscard]] bool willMultiplicationOverflow(T a, T b)
{
    if (a == 0 || b == 0) {
        // Multiplication with zero never overflows
        return false;
    }
    return a > std::numeric_limits<T>::max() / b;
}

} // namespace utils::math
