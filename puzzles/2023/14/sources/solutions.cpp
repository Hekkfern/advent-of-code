#include "solutions.hpp"

#include "Rocks.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/join.hpp>
#include <utils/File.hpp>

namespace aoc_2023_14 {

// ---------- Private Methods ----------

/**
 * @brief      Parses the whole input file and generates a flatten grid.
 *
 * @details    The flatten grid contains the rows of the grid one after another.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     Parsed data.
 */
Rocks parseInput(std::filesystem::path const& filePath)
{
    std::vector<std::string> rocks;
    utils::file::parseAndIterate(
        filePath, [&rocks](std::string_view const line) -> void {
            rocks.emplace_back(line);
        });
    return Rocks{
        rocks | ranges::views::join | ranges::to<std::vector>,
        rocks[0].size(),
        rocks.size()};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto rocks{parseInput(filePath)};
    rocks.shiftNorth();
    return std::to_string(rocks.calculateLoad());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_14
