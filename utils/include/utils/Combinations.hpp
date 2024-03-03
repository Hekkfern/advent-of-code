#pragma once

namespace utils::combinations {

template <class T>
void forEachCombination(std::vector<T>& container, std::function<>)
{
}

/**
 * @brief Generates all the possible combinations from a set of collections and applies a function to each combination.
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
