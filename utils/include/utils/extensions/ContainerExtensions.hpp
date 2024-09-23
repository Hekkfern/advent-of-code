#pragma once

#include "../Math.hpp"
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

namespace utils::extensions {

/**
 * @brief      Performs a rotation in the elements of a vector. Modifies the
 *             vector in-place. If the operation is invalid, does nothing.
 *
 * @param      numbers  The vector of integers to operate on. This vector is
 *                      modified directly.
 * @param[in]  offset   The number of positions to move the values, which can be
 *                      positive or negative.
 *                        * >0: rotate to the right
 *                        * <0: rotate to the left
 *
 * @test       Given numbers={1, 2, 3, 4, 5, 6, 7} and offset=3, the result is
 *             {5, 6, 7, 1, 2, 3, 4}.
 * @test       Given numbers={1, 2, 3, 4, 5, 6, 7} and offset=-3, the result is
 *             {4, 5, 6, 7, 1, 2, 3}.
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
 * @param[in,out] numbers   The list of integers to operate on. This vector is
 *                          modified directly.
 * @param[in]     position  The index of the value to move. This should be a
 *                          valid index within the vector bounds.
 * @param[in]     offset    The number of positions to move the value, which can
 *                          be positive or negative.
 *                            * >0: moves the item to the right
 *                            * <0: moves the item to the left
 *
 * @test          Given numbers={1, 2, 3, 4, 5, 6, 7}, position=0 and offset=3,
 *                the result is {2, 3, 4, 1, 5, 6, 7}.
 * @test          Given numbers={1, 2, 3, 4, 5, 6, 7}, position=0 and offset=-3,
 *                the result is {2, 3, 4, 1, 5, 6, 7}.
 *
 * @tparam        T         Type of the content of the list.
 *
 * @{
 */
template <typename T>
void moveValueCircularly(
    std::list<T>& numbers, std::size_t const position, int32_t const offset)
{
    std::size_t const n{numbers.size()};
    if (n <= 1 || position >= n || offset == 0) {
        return; // Do nothing
    }

    auto it{numbers.begin()};
    std::advance(it, position);

    /**
     * @brief      Advance an iterator by the given amount, with wrap-around
     *
     * @param[in]  it      The iterator to move
     * @param[in]  amount  The amount of position to move @p it
     * @param[in]  begin   The begin iterator (low limit)
     * @param[in]  end     The end iterator (high limit)
     *
     * @return     { description_of_the_return_value }
     */
    auto advance = [](auto it, int64_t amount, auto begin, auto end) {
        auto pos = it;
        while (amount > 0) {
            if (pos == end) {
                pos = begin;
            }
            ++pos;
            --amount;
        }
        return pos;
    };
    /**
     * @brief      { lambda_description }
     *
     * @param[in]  it     The iterator
     * @param[in]  value  The value
     *
     * @return     { description_of_the_return_value }
     */
    auto positive_offset = [&numbers, &advance](auto it, int64_t value) {
        // For zero offset, we need a no-op splice, and since splice
        // inserts before the given iterator, we need next
        auto pos = std::next(it);

        // Moving an element size-1 times ends up in the same position
        int64_t amount = (value) % (std::ssize(numbers) - 1);

        // Get the new position
        return advance(pos, amount, numbers.begin(), numbers.end());
    };
    /**
     * @brief      { lambda_description }
     *
     * @param[in]  it     The iterator
     * @param[in]  value  The value
     *
     * @return     { description_of_the_return_value }
     */
    auto negative_offset = [&numbers, &advance](auto it, int64_t value) {
        // Use reverse iterator to move in reverse.
        // make_reverse_iterator already returns an offset iterator
        // so no need for std::next()
        auto pos = std::make_reverse_iterator(it);

        // Moving an element size-1 times ends up in the same position
        int64_t amount = (-value) % (std::ssize(numbers) - 1);

        pos = advance(pos, amount, numbers.rbegin(), numbers.rend());

        // numbers.rend() maps to numbers.begin() which would make the splice
        // insert the element at the beginning of the list. When we move
        // an element past the first element, we actually want it at
        // the end of the list.
        if (pos == numbers.rend()) {
            return numbers.end();
        } else {
            return pos.base();
        }
    };

    if (offset > 0) {
        // Use the positive offset for positive numbers
        numbers.splice(positive_offset(it, offset), numbers, it);
    } else if (offset < 0) {
        // Use the negative offset for negative numbers
        numbers.splice(negative_offset(it, offset), numbers, it);
    }
}
template <typename T>
void moveValueCircularly(
    std::vector<T>& numbers, std::size_t const position, int32_t const offset)
{
    std::size_t const n{numbers.size()};
    if (n <= 1 || position >= n || offset == 0) {
        return; // Do nothing
    }

    std::list<T> numbersList{numbers.begin(), numbers.end()};

    moveValueCircularly<T>(numbersList, position, offset);

    numbers = std::vector<T>{numbersList.begin(), numbersList.end()};
}
/** }@ */

} // namespace utils::extensions
