#include "solutions.hpp"

#include <array>
#include <numeric>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2021_1 {

// ---------- Private Methods ----------

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t increaseCounter = 0U;
    uint32_t entryIndex = 0U;
    uint32_t lastValue = 0U;

    utils::file::parseAndIterate(
        filePath,
        [&increaseCounter, &entryIndex, &lastValue](
            std::string_view const line) {
            auto const value = utils::string::toNumber<uint32_t>(line);
            if (entryIndex > 0U && value > lastValue) {
                ++increaseCounter;
            }
            lastValue = *value;
            entryIndex++;
        });

    return std::to_string(increaseCounter);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    constexpr uint32_t SlidingWindowSize{3U};

    uint32_t increaseCounter = 0U;
    uint32_t entryIndex = 0U;
    std::array<uint32_t, SlidingWindowSize + 1> values{};

    utils::file::parseAndIterate(
        filePath,
        [&increaseCounter, &entryIndex, &values](std::string_view const line) {
            auto const value = utils::string::toNumber<uint32_t>(line);
            if (entryIndex < SlidingWindowSize) {
                // add the new value
                values.at(entryIndex) = *value;
            } else {
                values.back() = *value;
                // check if it is increasing
                auto const currentSum = std::accumulate(
                    std::begin(values) + 1, std::end(values), 0U);
                auto const previousSum = std::accumulate(
                    std::begin(values), std::end(values) - 1, 0U);
                if (currentSum > previousSum) {
                    ++increaseCounter;
                }
                // clean
                std::rotate(
                    std::begin(values),
                    std::begin(values) + 1,
                    std::end(values));
            }
            entryIndex++;
        });

    return std::to_string(increaseCounter);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2021_1
