#include "solutions.hpp"

#include <fstream>
#include <utils/StringUtils.hpp>

namespace aoc_2021_01 {

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    int64_t increaseCounter = 0;
    int64_t numLines = 0;
    int64_t lastValue = 0;

    while (std::getline(stream, line)) {
        numLines++;
        int64_t value = utils::StringUtils::toNumber<int64_t>(line);
        if (numLines > 1 && value > lastValue) {
            ++increaseCounter;
        }
        lastValue = value;
    }

    return std::to_string(increaseCounter);
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

} // namespace aoc_2021_01
