#include "solutions.hpp"

#include <fstream>
#include <list>
#include <optional>
#include <range/v3/all.hpp>
#include <utils/ListExtensions.hpp>
#include <utils/String.hpp>

namespace aoc_2022_20 {

// ---------- Private Methods ----------

/**
 * @brief      Parses the input file and extracts a list of integers.
 *
 * @param[in]      filename  The filename.
 *
 * @return     List of the parsed numbers.
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
 * @brief      { function_description }
 *
 * @param      list  The list
 *
 * @return     { description_of_the_return_value }
 */
int32_t mixNumbers(std::vector<int32_t> const& list)
{
    std::list<int32_t> indexList(list.size());
    ranges::iota(indexList, 0);
    // reorder the items
    for (std::size_t i{0U}; i < list.size(); ++i) {
        // skip the values with zero because it implies no movement
        if (list.at(i) == 0) {
            continue;
        }
        std::size_t const oldIndex{static_cast<std::size_t>(ranges::distance(
            std::begin(indexList), ranges::find(indexList, i)))};
        utils::containers::circularMoveXPositions(
            indexList, oldIndex, static_cast<ssize_t>(list.at(i)));
    }
    // collect the important values from the list
    std::size_t zeroIndex{static_cast<std::size_t>(
        ranges::distance(std::begin(list), ranges::find(list, 0)))};
    zeroIndex = static_cast<std::size_t>(ranges::distance(
        std::begin(indexList), ranges::find(indexList, zeroIndex)));
    int32_t level{0};
//    for (std::size_t i{0U}; i < 3U; ++i) {
//        level += list[static_cast<std::size_t>(
//            indexList[((1000U * i) + 1000U + zeroIndex)])];
//    }
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
