#pragma once

#include "../Math.hpp"
#include <algorithm>
#include <vector>

namespace utils::extensions {

/**
 * @brief      Performs a rotation in the elements of a vector.
 *
 * @param      numbers  The vector of integers to operate on. This vector is
 *                      modified directly.
 * @param[in]  offset   The number of positions to move the values, which can be
 *                      positive or negative.
 *                        >0: rotate to the right
 *                        <0: rotate to the left
 *
 * @tparam     T        Type of the content of the vector.
 */
template <typename T>
void rotate(std::vector<T>& numbers, int32_t const offset)
{
    auto const n{numbers.size()};
    auto const normalizedOffset{static_cast<std::size_t>(
        utils::math::modulusFloor(offset, static_cast<int32_t>(n)))};
    if (n <= 1 || normalizedOffset == 0) {
        return; // Do nothing
    }

    std::rotate(
        numbers.rbegin(), numbers.rbegin() + normalizedOffset, numbers.rend());
}

/**
 * @brief         Moves the value at a specified index in a vector circularly by
 *                a given offset. Modifies the vector in-place. If the operation
 *                is invalid, does nothing.
 *
 * @param[in,out] numbers   The vector of integers to operate on. This vector is
 *                          modified directly.
 * @param[in]     position  The index of the value to move. This should be a
 *                          valid index within the vector bounds.
 * @param[in]     offset    The number of positions to move the value, which can
 *                          be positive or negative.
 *
 * @tparam        T         Type of the content of the vector.
 */
template <typename T>
void moveValueCircularly(
    std::vector<T>& numbers, std::size_t position, int32_t const offset)
{
    std::size_t const n{numbers.size()};
    auto const normalizedOffset{
        utils::math::modulusFloor(offset, static_cast<int32_t>(n))};
    if (n <= 1 || position >= n || normalizedOffset == 0) {
        return; // Do nothing
    }

    // TODO
}

} // namespace utils::extensions
