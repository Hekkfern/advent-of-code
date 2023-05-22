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

template <SignedIntegerType T = int32_t>
bool circularMoveFromXToY(
    std::list<T>& list, std::size_t const oldIndex, std::size_t const newIndex)
{
    if (list.size() < 2U) {
        return false;
    }
    if (oldIndex >= list.size() || newIndex >= list.size()) {
        return false;
    }
    if (oldIndex == newIndex) {
        return true;
    }
    // Get the iterators to the elements at the specified positions
    auto iter1{std::begin(list)};
    std::advance(iter1, oldIndex);
    auto iter2{std::begin(list)};
    std::advance(iter2, newIndex);
    // Determine the direction of the move and adjust the positions of all
    // elements in between
    if (oldIndex < newIndex) {
        list.splice(std::next(iter2), list, iter1);
    } else {
        list.splice(iter2, list, iter1);
    }
    return true;
}

/**
 * @brief      Moves the item from one position to another, and slides all
 * the other items accordingly.
 *
 * @param[in] list a
 * @param[in]  oldIndex  The old index.
 * @param[in]  positions  The new index.
 */
template <SignedIntegerType T = int32_t>
bool circularMoveXPositions(
    std::list<T>& list, std::size_t const oldIndex, ssize_t const positions)
{
    if (positions == 0U) {
        return false;
    }
    ssize_t const newIndex{utils::integermath::modulusFloor(
        static_cast<ssize_t>(oldIndex) + positions,
        static_cast<ssize_t>(list.size()))};
    return circularMoveFromXToY<T>(
        list, oldIndex, static_cast<std::size_t>(newIndex));
}

/**
 * @brief      Rotate the list some positions to the left.
 *
 * @param[in] list a
 * @param[in]  amount  The amount of positions to rotate.
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

    auto it{std::begin(list)};
    std::advance(it, rotations);
    list.splice(std::end(list), list, std::begin(list), it);
    return true;
}
/**
 * @brief      Rotate the list some positions to the right.
 *
 * @param[in] list a
 * @param[in]  amount  The amount of positions to rotate.
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

    auto it{list.end()};
    std::advance(it, -rotations);
    list.splice(std::begin(list), list, it, std::end(list));
    return true;
}

/**
 * @brief      Advance an iterator by the given amount, with wrap-around.
 *
 * @param      it      The iterator
 * @param[in]  amount  The amount
 *
 * @return     { description_of_the_return_value }
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
 * @brief      Advance an iterator by the given amount, with wrap-around.
 *
 * @param      it      The iterator
 * @param[in]  amount  The amount
 *
 * @return     { description_of_the_return_value }
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
