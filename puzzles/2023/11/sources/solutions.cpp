#include "solutions.hpp"

#include "GalaxyMap.hpp"
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/enumerate.hpp>
#include <utils/File.hpp>

namespace aoc_2023_11 {

// ---------- Private Methods ----------

GalaxyMap parseInput(std::filesystem::path const& filePath)
{
    GalaxyMap galaxyMap;

    // parse file and check for empty rows
    utils::file::parseAndIterateWithIndex(
        filePath,
        [&galaxyMap](
            std::size_t const rowIndex, std::string_view const line) -> void {
            std::size_t galaxyCount{0ULL};
            for (auto const [colIndex, c] : line | ranges::views::enumerate) {
                if (c == '#') {
                    galaxyMap.mGalaxies.emplace_back(colIndex, rowIndex);
                    ++galaxyCount;
                }
            }
            // check if the row was empty
            if (galaxyCount == 0ULL) {
                galaxyMap.mEmptyRows.emplace_back(rowIndex);
            }
        });
    // check for empty columns
    //TODO

    return galaxyMap;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_11