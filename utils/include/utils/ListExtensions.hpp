#pragma once

#include "Concepts.hpp"
#include "IntegerMath.hpp"
#include <iterator>
#include <list>
#include <ostream>

namespace {

template <SignedIntegerType T = int32_t>
using iterator = typename std::list<T>::iterator;

} // namespace

namespace utils::containers {

/**
 * @brief      Moves one item from one position to another, and slides the items
 *             in between.
 *
 * @param[in]  list      The list to operate with.
 * @param[in]  oldIndex  The current index of the item to move.
 * @param[in]  newIndex  The new index where to relocate it.
 *
 * @tparam     T         Type of the items of the list.
 *
 * @return     True if the operation was successful. False, otherwise.
 */
template <SignedIntegerType T = int32_t>
bool moveFromXToY(
    std::list<T>& list, std::size_t const oldIndex, std::size_t const newIndex)
{
    /* Validations of the input parameters */
    if (list.size() < 2U) {
        return false;
    }
    if (oldIndex >= list.size() || newIndex >= list.size()) {
        return false;
    }
    if (oldIndex == newIndex) {
        return true;
    }
    /* Get the iterators to the elements at the specified positions */
    auto iter1{std::next(std::begin(list), static_cast<int64_t>(oldIndex))};
    auto iter2{std::next(std::begin(list), static_cast<int64_t>(newIndex))};
    /* Determine the direction of the move and adjust the positions of all
     * elements in between */
    if (oldIndex < newIndex) {
        list.splice(std::next(iter2), list, iter1);
    } else {
        list.splice(iter2, list, iter1);
    }
    return true;
}

/**
 * @brief      Moves the item in one position by a certain amount of positions,
 *             and slides all the other items accordingly.
 *
 * @param[in]  list       The list to operate with.
 * @param[in]  oldIndex   The current index of the item to move.
 * @param[in]  positions  The number of positions to move. It can be a positive
 *                        (move to the right) or negative (move to the left).
 *
 * @tparam     T          Type of the items of the list.
 *
 * @return     True if the operation was successful. False, otherwise.
 */
template <SignedIntegerType T = int32_t>
bool circularMoveXPositions(
    std::list<T>& list, std::size_t const oldIndex, int64_t const positions)
{
    /* Validations of the input parameters */
    if (list.size() < 2U) {
        return false;
    }
    if (oldIndex >= list.size()) {
        return false;
    }
    // Wrap around the number of positions if necessary
    int64_t numPositions = positions % static_cast<int64_t>(list.size());
    if (numPositions == 0) {
        return false;
    }

    // Find the iterator pointing to the item to move
    auto itemIter = std::next(std::begin(list), static_cast<int64_t>(oldIndex));

    // Move the item using the splice method
    if (numPositions > 0) {
        auto nextIter = std::next(itemIter, numPositions);
        list.splice(nextIter, list, itemIter);
    } else {
        auto prevIter = std::prev(itemIter, -numPositions);
        if (prevIter == list.end()) {
            // Special case: Moving to a position after the end of the list
            list.splice(list.end(), list, itemIter);
        } else {
            list.splice(prevIter, list, itemIter);
        }
    }
    return true;
}

/**
 * @brief      Rotate the list some positions to the left.
 *
 * @param[in]  list    The list to operate with.
 * @param[in]  amount  The amount of positions to rotate.
 *
 * @tparam     T       Type of the items of the list.
 *
 * @return     True if the operation was successful. False, otherwise.
 */
template <SignedIntegerType T = int32_t>
bool circularRotateLeft(std::list<T>& list, std::size_t const amount = 1U)
{
    if (list.size() < 2U || amount == 0U) {
        return false;
    }
    auto rotations{amount % list.size()};
    if (rotations == 0U) {
        /* No need to rotate if rotations is a multiple of the list size */
        return false;
    }

    auto it{std::next(std::begin(list), static_cast<int64_t>(rotations))};
    list.splice(std::end(list), list, std::begin(list), it);
    return true;
}
/**
 * @brief      Rotate the list some positions to the right.
 *
 * @param[in]  list    The list to operate with.
 * @param[in]  amount  The amount of positions to rotate.
 *
 * @tparam     T       Type of the items of the list.
 *
 * @return     True if the operation was successful. False, otherwise.
 */
template <SignedIntegerType T = int32_t>
bool circularRotateRight(std::list<T>& list, std::size_t const amount = 1U)
{
    if (list.size() < 2U || amount == 0U) {
        return false;
    }
    auto rotations{amount % list.size()};
    if (rotations == 0U) {
        /* No need to rotate if rotations is a multiple of the list size */
        return false;
    }

    auto it{std::next(list.end(), -static_cast<int64_t>(rotations))};
    list.splice(std::begin(list), list, it, std::end(list));
    return true;
}

/**
 * @brief      Moves forward an iterator by the given amount, with wrap-around.
 *
 * @param[in]  list    The list to operate with.
 * @param[in]  it      The iterator to advance.
 * @param[in]  amount  The amount of positions to advance.
 *
 * @tparam     T       Type of the items of the list.
 *
 * @return     The new iterator.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] iterator<T> circularNext(
    std::list<T> const& list, iterator<T>& it, std::size_t const amount = 1U)
{
    if (list.empty()) {
        throw std::out_of_range("CircularList is empty");
    }
    iterator<T> nextIt{it};
    std::size_t counter{amount};
    while (counter > 0) {
        nextIt = std::next(it) == std::end(list)
            ? std::begin(list)
            : std::next(it);
        --counter;
    }
    return nextIt;
}

/**
 * @brief      Moves backwards an iterator by the given amount, with
 *             wrap-around.
 *
 * @param[in]  list    The list to operate with.
 * @param[in]  it      The iterator to advance.
 * @param[in]  amount  The amount of positions to advance.
 *
 * @tparam     T       Type of the items of the list.
 *
 * @return     The new iterator.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] iterator<T> circularPrev(
    std::list<T> const& list, iterator<T>& it, std::size_t const amount = 1U)
{
    if (list.empty()) {
        throw std::out_of_range("CircularList is empty");
    }
    typename std::list<T>::reverse_iterator prevIt{it};
    std::size_t counter{amount};
    while (counter > 0) {
        prevIt = std::next(it) == std::end(list)
            ? std::begin(list)
            : std::next(it);
        --counter;
    }
    return prevIt;
}

} // namespace utils::containers
