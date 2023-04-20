#include "solutions.hpp"

#include <fstream>
#include <list>
#include <optional>
#include <utils/String.hpp>

namespace aoc_2022_20 {

// ---------- Private Methods ----------

std::list<int32_t> parseInput(const std::string& filename)
{
    std::ifstream fileStream{filename};
    std::list<int32_t> outList;
    std::string line;
    while (std::getline(fileStream, line)) {
        outList.emplace_back(utils::string::toNumber<int32_t>(line));
    }
    return outList;
}

uint32_t calculatePositionsToMove(
    const std::list<int32_t>& numberList, const int32_t value)
{
    return static_cast<uint32_t>(std::abs(value)) % (numberList.size() - 1U);
}

/**
 * @brief Advances an iterator by the given amount, with wrap-around
 */
auto advanceIterator(auto it, const uint32_t amount, auto begin, auto end)
{
    auto pos{it};
    uint32_t counter{amount};
    while (counter > 0U) {
        if (pos == end)
            pos = begin;
        ++pos;
        --counter;
    }
    return pos;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    (void)filename;
    return "";
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_20