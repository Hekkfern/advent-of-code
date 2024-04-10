#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <range/v3/algorithm/contains.hpp>
#include <vector>

namespace utils::cache::LoopCache {

/**
 * @brief         Executes a given action on an item repeatedly until a maximum
 *                number of iterations is reached or a loop is detected.
 *
 * @details       Loops are identified and managed to prevent infinite
 *                iterations, using internal caching mechanisms.
 *
 * @tparam        T                 Type of the item to be modified.
 *
 * @param[in,out] item              The item to be modified through
 *                                  iterationAction.
 * @param[in]     maxNumIterations  The maximum number of iterations to perform.
 * @param[in]     iterationAction   The action to perform in each iteration. It
 *                                  takes a reference to T and modifies it.
 *
 * @note          The function asserts that iterationAction is not an empty
 *                function object.
 *
 */
template <typename T>
void run(
    T& item,
    int64_t const maxNumIterations,
    std::function<void(T& itemToChange)> const& iterationAction)
{
    assert(iterationAction);

    int64_t cycleCounter{0LL};
    std::vector<T> history;
    history.reserve(256);
    while (
        cycleCounter < maxNumIterations && !ranges::contains(history, item)) {
        history.emplace_back(item);
        iterationAction(item);
        ++cycleCounter;
    }
    int64_t const offset{
        std::distance(history.begin(), ranges::find(history, item))};
    int64_t const cycleLength{cycleCounter - offset};
    if (maxNumIterations > offset) {
        item = history[offset + (maxNumIterations - offset) % cycleLength];
    } else {
        item = history.back();
    }
}

} // namespace utils::cache::LoopCache
