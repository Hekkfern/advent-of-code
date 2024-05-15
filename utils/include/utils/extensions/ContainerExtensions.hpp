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
 *
 * @tparam     T        Type of the content of the vector.
 */
template <typename T>
void rotate(std::vector<T>& numbers, int32_t const offset)
{
    std::size_t const n{numbers.size()};
    if (offset == 0 || n <= 1) {
        return; // Do nothing
    }

    // TODO
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
    auto const k{utils::math::modulusFloor(offset, static_cast<int32_t>(n))};
    if (position >= n || n == 0 || k == 0) {
        return; // Do nothing
    }

    // TODO
}

} // namespace utils::extensions
