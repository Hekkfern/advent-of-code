#include "solutions.hpp"

#include <fstream>
#include <list>
#include <optional>
#include <range/v3/all.hpp>
#include <utils/IntegerMath.hpp>
#include <utils/String.hpp>

namespace aoc_2022_20 {

// ---------- Private Methods ----------

/**
 * @brief      { function_description }
 *
 * @param      filename  The filename
 *
 * @return     { description_of_the_return_value }
 */
std::vector<int32_t> parseInput(std::string const& filename)
{
    std::ifstream fileStream{filename};
    std::vector<int32_t> outList;
    std::string line;
    while (std::getline(fileStream, line)) {
        outList.emplace_back(utils::string::toNumber<int32_t>(line));
    }
    return outList;
}

/**
 * @brief      Calculates the index.
 *
 * @param      list   The list
 * @param[in]  index  The index
 *
 * @return     The index.
 */
std::size_t refineIndex(std::vector<int32_t> const& list, int32_t const index)
{
    int32_t const divisor{static_cast<int32_t>(list.size() - 1)};
    if (index < 0 || index > divisor) {
        // https://www.geeksforgeeks.org/modulus-on-negative-numbers/
        return static_cast<std::size_t>(
            utils::integermath::modulusFloor(index, divisor));
    }
    return static_cast<std::size_t>(index);
}

/**
 * @brief      Calculates the new position.
 *
 * @param      list           The list
 * @param[in]  oldIndex          The index
 * @param[in]  movementValue  The movement value
 *
 * @return     The new position.
 */
std::size_t calculateNewIndex(
    std::vector<int32_t> const& list,
    std::size_t const oldIndex,
    int32_t const movementValue)
{
    return refineIndex(list, static_cast<int32_t>(oldIndex) + movementValue);
}

/**
 * @brief      { function_description }
 *
 * @param      list      The list
 * @param[in]  oldIndex  The old index
 * @param[in]  newIndex  The new index
 */
void moveItem(
    std::vector<int32_t>& list,
    std::size_t const oldIndex,
    std::size_t const newIndex)
{
    if (oldIndex > newIndex) {
        std::rotate(
            std::rend(list) - static_cast<int>(oldIndex) - 1,
            std::rend(list) - static_cast<int>(oldIndex),
            std::rend(list) - static_cast<int>(newIndex));
    } else {
        std::rotate(
            std::begin(list) + static_cast<int>(oldIndex),
            std::begin(list) + static_cast<int>(oldIndex) + 1,
            std::begin(list) + static_cast<int>(newIndex) + 1);
    }
}

/**
 * @brief      { function_description }
 *
 * @param      list  The list
 *
 * @return     { description_of_the_return_value }
 */
int32_t mixNumbers(std::vector<int32_t> const& list)
{
    std::vector<int32_t> indexList(list.size());
    ranges::iota(indexList, 0);
    // reorder the items
    for (std::size_t i{0U}; i < list.size(); ++i) {
        if (list.at(i) == 0) {
            continue;
        }
        std::size_t const oldIndex{static_cast<std::size_t>(ranges::distance(
            std::begin(indexList), ranges::find(indexList, i)))};
        std::size_t newIndex{calculateNewIndex(list, oldIndex, list.at(i))};
        moveItem(
            indexList,
            static_cast<size_t>(oldIndex),
            static_cast<size_t>(newIndex));
    }
    // collect the important values from the list
    std::size_t zeroIndex{static_cast<std::size_t>(
        ranges::distance(std::begin(list), ranges::find(list, 0)))};
    zeroIndex = static_cast<std::size_t>(ranges::distance(
        std::begin(indexList), ranges::find(indexList, zeroIndex)));
    int32_t level{0};
    for (std::size_t i{0U}; i < 3U; ++i) {
        level += list[static_cast<std::size_t>(
            indexList[((1000U * i) + 1000U + zeroIndex)])];
    }
    return level;

    return 1;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    auto numberList{parseInput(filename)};
    return std::to_string(mixNumbers(numberList));
}

std::string solvePart2(std::string const& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_20
