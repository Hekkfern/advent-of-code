#include "solutions.hpp"

#include <array>
#include <fstream>
#include <utils/StringUtils.hpp>

namespace aoc_2021_01 {

std::string solvePart1(const std::string& filename)
{
    std::ifstream stream{ filename };
    std::string line;
    uint32_t increaseCounter = 0;
    uint32_t entryIndex = 0;
    uint32_t lastValue = 0;

    while (std::getline(stream, line)) {
        uint32_t value = utils::StringUtils::toNumber<uint32_t>(line);
        if (entryIndex > 0 && value > lastValue) {
            ++increaseCounter;
        }
        lastValue = value;
        entryIndex++;
    }

    return std::to_string(increaseCounter);
}

std::string solvePart2(const std::string& filename)
{
    constexpr int32_t SlidingWindowSize{ 3 };

    std::ifstream stream{ filename };
    std::string line;
    uint32_t increaseCounter = 0;
    uint32_t entryIndex = 0;
    std::array<int32_t, SlidingWindowSize + 1> sums{};
    uint32_t slidingWindowIndex = 0;

    while (std::getline(stream, line)) {
        uint32_t value = utils::StringUtils::toNumber<uint32_t>(line);
        // add the new value in every sum
        slidingWindowIndex = entryIndex % SlidingWindowSize;
        for (uint32_t groupIndex = 0; (groupIndex < SlidingWindowSize)
             && (entryIndex >= groupIndex);
             ++groupIndex) {
            sums[slidingWindowIndex - groupIndex] += value;
        }
        // check if it is increasing
        if (entryIndex >= SlidingWindowSize) {
            if (sums[slidingWindowIndex] > sums[slidingWindowIndex - 1]) {
                ++increaseCounter;
            }
            // clean
            sums[slidingWindowIndex] = 0;
        }
        entryIndex++;
    }

    return std::to_string(increaseCounter);
}

} // namespace aoc_2021_01
