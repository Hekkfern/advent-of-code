#include "solutions.hpp"

#include "Pattern.hpp"
#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
#include <utils/String.hpp>
#include <vector>

namespace aoc_2023_13 {

// ---------- Private Methods ----------

std::optional<Pattern> parsePattern(std::ifstream& fileStream)
{
    std::vector<std::string> outList;

    std::string line;
    while (std::getline(fileStream, line)) {
        auto lineStr{utils::string::trim(line)};
        if (lineStr.empty()) {
            break;
        }
        outList.emplace_back(std::move(lineStr));
    }

    if (outList.empty()) {
        return {};
    }
    return Pattern{std::move(outList)};
}

std::vector<Pattern> parseInput(std::filesystem::path const& filePath)
{
    std::ifstream fileStream{filePath.string()};
    if (!fileStream.is_open()) {
        return {};
    }

    std::vector<Pattern> outList;
    while (auto pattern{parsePattern(fileStream)}) {
        if (pattern) {
            outList.emplace_back(std::move(*pattern));
        }
    }

    return outList;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const patterns{parseInput(filePath)};
    auto const result{ranges::fold_left(
        patterns,
        0ULL,
        [](uint64_t const accum, Pattern const& pattern) -> uint64_t {
            uint64_t value{0ULL};
            const auto verticalReflectionLines{
                pattern.searchVerticalReflectionLines()};
            for (const auto& verticalReflectionLine : verticalReflectionLines) {
                value += verticalReflectionLine.first + 1ULL;
            }
            const auto horizontalReflectionLines{
                pattern.searchHorizontalReflectionLines()};
            for (const auto& horizontalReflectionLine :
                 horizontalReflectionLines) {
                value += 100ULL * (horizontalReflectionLine.first + 1ULL);
            }
            return accum + value;
        })};
    return std::to_string(result);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_13
