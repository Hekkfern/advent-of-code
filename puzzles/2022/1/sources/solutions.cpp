#include "solutions.hpp"

#include <array>
#include <fstream>
#include <range/v3/all.hpp>
#include <utils/StringUtils.hpp>

namespace aoc_2022_1 {

// ---------- Private Methods ----------

constexpr uint32_t TopQuantity{ 3U };

/**
 * @brief Checks whether the candidate can be inserted in the provided top
 * ranking.
 *
 * @param[in,out] highestSums Ranking to use.
 * @param[in] candidate Candidate value to insert into the ranking.
 */
void insertInRanking(
    std::array<uint32_t, TopQuantity>& highestSums,
    uint32_t candidate)
{
    auto it = ranges::find_if(
        highestSums, [candidate](uint32_t value) { return candidate > value; });
    if (it != std::end(highestSums)) {
        std::copy_backward(
            it, std::end(highestSums) - 1, std::end(highestSums));
        *it = candidate;
    }
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

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
    insertInRanking(highestSums, currentSum);

    return std::to_string(ranges::accumulate(highestSums, 0U));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_1
