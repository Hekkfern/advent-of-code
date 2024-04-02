#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <utils/Concepts.hpp>

namespace utils::cache::LoopCache {

namespace detail {
template <typename T>
struct VisitedInfo {
    T modifiedItem;
    uint64_t iterationCounter;
};
} // namespace detail

/**
 * @brief         Executes a given action on an item repeatedly until a maximum
 *                number of iterations is reached or a loop is detected.
 *
 * @details       Loops are identified and managed to prevent infinite
 *                iterations, using internal caching mechanisms.
 *
 * @tparam        T                 Type of the item to be modified. Must be
 *                                  equality comparable and hashable.
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
 *                Requirements:
 * - T must satisfy std::equality_comparable and Hashable concepts.
 * - iterationAction must be a valid std::function that modifies its parameter
 *   of type T&.
 */
template <typename T>
    requires std::equality_comparable<T> && Hashable<T>
void run(
    T& item,
    std::size_t const maxNumIterations,
    std::function<void(T& itemToChange)> const& iterationAction)
{
    assert(iterationAction);
    uint64_t iterationCounter{0ULL};
    std::unordered_map<T, uint64_t> loops;
    std::unordered_map<T, detail::VisitedInfo<T>> visited;
    bool finishManually{false};
    while (iterationCounter < maxNumIterations) {
        if (auto const loopIt{loops.find(item)};
            loopIt != loops.cend() && !finishManually) {
            // loop found in the cache
            if (iterationCounter + loopIt->second <= maxNumIterations) {
                iterationCounter += loopIt->second;
            } else {
                finishManually = true;
                iterationAction(item);
                ++iterationCounter;
            }
        } else {
            // loop not found in the cache
            if (auto const visitedIt{visited.find(item)};
                visitedIt != visited.cend()) {
                // action result cached
                if (!loops.contains(item)) {
                    uint64_t const loopLength{
                        iterationCounter - visitedIt->second.iterationCounter};
                    loops.emplace(item, loopLength);
                    iterationCounter += loopLength;
                } else {
                    item = visitedIt->second.modifiedItem;
                    ++iterationCounter;
                }
            } else {
                // action result not cached
                auto const originalItem{item};
                iterationAction(item);
                visited.emplace(
                    originalItem,
                    detail::VisitedInfo<T>{item, iterationCounter});
                ++iterationCounter;
            }
        }
    }
}

} // namespace utils::cache::LoopCache
