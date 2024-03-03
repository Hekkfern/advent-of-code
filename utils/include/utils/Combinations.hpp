#pragma once

#include <functional>
#include <range/v3/algorithm/sort.hpp>
#include <vector>

namespace utils::combinations {

namespace detail {
template <typename T, typename Function>
void forEachCombinationHelper(
    std::vector<T> const& container,
    std::size_t K,
    Function&& function,
    std::vector<T>& combination,
    std::size_t start)
{
    if (combination.size() == K) {
        function(combination);
        return;
    }

    for (std::size_t i{start}; i < container.size(); ++i) {
        combination.emplace_back(container[i]);
        forEachCombinationHelper(
            container, K, std::forward<Function>(function), combination, i + 1);
        combination.pop_back();
        // Skip duplicates
        while (i < container.size() - 1 && container[i] == container[i + 1]) {
            ++i;
        }
    }
}
} // namespace detail

/**
 * @brief Calculates how many different ways you can choose "K" items from all
 * the items in the container without repetition and without order.
 *
 * @param[in] N Total number of elements.
 * @param[in] K Number of elements of the group.
 *
 * @return Total amount of combinations.
 */
uint64_t calculateNumberCombinations(std::size_t const N, std::size_t K)
{
    if (K > N) {
        return 0;
    }
    if (K * 2 > N) {
        K = N - K;
    }
    if (K == 0) {
        return 1;
    }
    size_t result = N;
    for (size_t i{2ULL}; i <= K; ++i) {
        result *= (N - i + 1ULL);
        result /= i;
    }
    return result;
}

template <typename T, typename Function>
void forEachCombination(
    std::vector<T> container, std::size_t K, Function&& function)
{
    std::vector<T> combination;
    ranges::sort(container);
    detail::forEachCombinationHelper(
        container, K, std::forward<Function>(function), combination, 0);
}

} // namespace utils::combinations
