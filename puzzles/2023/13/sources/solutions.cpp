#include "solutions.hpp"

#include "Pattern.hpp"
#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/view/enumerate.hpp>
#include <utils/String.hpp>
#include <vector>

namespace aoc_2023_13 {

// ---------- Private Methods ----------

/**
 * @brief         Parses a single pattern of the input file.
 *
 * @param[in,out] fileStream  The file stream.
 *
 * @return        Information of the pattern.
 */
std::optional<Pattern> parsePattern(std::ifstream& fileStream)
{
    std::vector<uint64_t> rows;
    std::vector<uint64_t> cols;

    std::string line;
    while (std::getline(fileStream, line)) {
        auto const lineStr{utils::string::trim(line)};
        if (lineStr.empty()) {
            break;
        }
        uint64_t rowValue{0ULL};
        for (auto const [colIndex, value] : ranges::views::enumerate(lineStr)) {
            rowValue = rowValue << 1 | (value == '#' ? 1 : 0);
            if (cols.size() == colIndex) {
                cols.emplace_back(value == '#' ? 1ULL : 0ULL);
            } else {
                cols[colIndex] = cols[colIndex] << 1 | (value == '#' ? 1 : 0);
            }
        }
        rows.emplace_back(rowValue);
    }

    if (rows.empty() || cols.empty()) {
        return {};
    }
    return Pattern{std::move(rows), std::move(cols)};
}

/**
 * @brief      Parses the whole input file.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     List of parsed patterns.
 */
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
        [](uint64_t const accumulated, Pattern const& pattern) -> uint64_t {
            uint64_t value{0ULL};
            const auto verticalReflectionLine{
                pattern.searchVerticalReflectionLine()};
            if (verticalReflectionLine) {
                value += verticalReflectionLine->first + 1ULL;
            }
            const auto horizontalReflectionLine{
                pattern.searchHorizontalReflectionLine()};
            if (horizontalReflectionLine) {
                value += 100ULL * (horizontalReflectionLine->first + 1ULL);
            }
            return accumulated + value;
        })};
    return std::to_string(result);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const patterns{parseInput(filePath)};
    auto const result{ranges::fold_left(
        patterns,
        0ULL,
        [](uint64_t const accumulated, Pattern const& pattern) -> uint64_t {
            uint64_t value{0ULL};
            const auto verticalReflectionLine{
                pattern.searchVerticalReflectionLineWithSingleFix()};
            if (verticalReflectionLine) {
                value += verticalReflectionLine->first + 1ULL;
            }
            const auto horizontalReflectionLine{
                pattern.searchHorizontalReflectionLineWithSingleFix()};
            if (horizontalReflectionLine) {
                value += 100ULL * (horizontalReflectionLine->first + 1ULL);
            }
            return accumulated + value;
        })};
    return std::to_string(result);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_13
