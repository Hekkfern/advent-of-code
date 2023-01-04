#include "solutions.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <numeric>
#include <utils/StringUtils.hpp>

namespace aoc_2022_1 {

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t highestSum = 0U;
    uint32_t currentSum = 0U;

    while (std::getline(stream, line)) {
        if (utils::StringUtils::trim(line).empty()) {
            highestSum = (currentSum > highestSum) ? currentSum : highestSum;
            currentSum = 0U;
        } else {
            currentSum += utils::StringUtils::toNumber<uint32_t>(line);
        }
    }

    return std::to_string(highestSum);
}

constexpr uint32_t TopQuantity{ 3U };

void insertInRanking(
    std::array<uint32_t, TopQuantity>& highestSums,
    uint32_t candidate)
{
    auto it = std::find_if(
        std::begin(highestSums),
        std::end(highestSums),
        [candidate](uint32_t value) { return candidate > value; });
    if (it != std::end(highestSums)) {
        std::copy_backward(
            it, std::end(highestSums) - 1, std::end(highestSums));
        *it = candidate;
    }
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    std::array<uint32_t, TopQuantity>
        highestSums{}; // the lower index, the higher sum of calories
    uint32_t currentSum = 0U;

    while (std::getline(stream, line)) {
        if (utils::StringUtils::trim(line).empty()) {
            insertInRanking(highestSums, currentSum);
            currentSum = 0U;
        } else {
            currentSum += utils::StringUtils::toNumber<uint32_t>(line);
        }
    }

    return std::to_string(
        std::accumulate(std::begin(highestSums), std::end(highestSums), 0U));
}

} // namespace aoc_2022_1