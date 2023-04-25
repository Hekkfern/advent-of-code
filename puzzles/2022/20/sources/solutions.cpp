#include "solutions.hpp"

#include <fstream>
#include <list>
#include <optional>
#include <range/v3/all.hpp>
#include <utils/String.hpp>

namespace aoc_2022_20 {

// ---------- Private Methods ----------

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

std::size_t
calculateIndex(std::vector<int32_t> const& list, int32_t const index)
{
    int32_t const divisor{static_cast<int32_t>(list.size() - 1)};
    if (index < 0 || index > divisor) {
        // https://www.geeksforgeeks.org/modulus-on-negative-numbers/
        return static_cast<std::size_t>((index % divisor + divisor) % divisor);
    }
    return static_cast<std::size_t>(index);
}

std::size_t calculateNewPosition(
    std::vector<int32_t> const& list,
    std::size_t const index,
    int32_t const movementValue)
{
    return index + calculateIndex(list, movementValue);
}

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

int32_t mixNumbers(std::vector<int32_t> const& list)
{
    std::vector<int32_t> indexList(list.size());
    ranges::iota(indexList, 0);
    // reorder the items
    for (std::size_t i{0U}; i < list.size(); ++i) {
        std::size_t const oldIndex{static_cast<std::size_t>(ranges::distance(
            std::begin(indexList), ranges::find(indexList, i)))};
        std::size_t newIndex{calculateNewPosition(list, oldIndex, list.at(i))};
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
