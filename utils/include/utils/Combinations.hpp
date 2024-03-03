#pragma once

namespace utils::combinations {

/**
 * @brief Calculates how many different ways you can choose "K" items from all the items in the container without repetition and without order.
 *
 * @tparam T
 *
 * @param[in] container
 * @param[in] K
 *
 * @return
 */
template <class T>
uint64_t calculateNumberCombinations(std::vector<T>& container, std::size_t K)
{
    size_t const N{container.size()};
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

template <class T>
void forEachCombination(std::vector<T>& container, std::function<>)
{
}

/**
 * @brief Generates all the possible combinations from a set of collections and
 * applies a function to each combination.
 *
 * https://www.fluentcpp.com/2022/03/18/how-to-generate-all-the-combinations-from-several-collections/
 *
 * @tparam Function
 * @tparam Ranges
 *
 * @param function
 * @param ranges
 */
template <typename Function, typename... Ranges>
void cartesianProduct(Function function, Ranges const&... ranges)
{
}

} // namespace utils::combinations
