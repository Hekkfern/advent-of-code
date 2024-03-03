#include "solutions.hpp"

#include "GalaxyMap.hpp"
#include <fstream>
#include <range/v3/view/enumerate.hpp>

namespace aoc_2023_11 {

// ---------- Private Methods ----------

GalaxyMap parseInput(std::filesystem::path const& filePath)
{
    GalaxyMap galaxyMap;

    std::ifstream fileStream{filePath};
    if (!fileStream.is_open()) {
        return {};
    }

    std::string line;
    // get first line to know how many columns it has
    std::getline(fileStream, line);
    auto const numCols{line.length()};
    std::vector<uint32_t> galaxiesPerColumn(numCols);
    auto parseLine =
        [&galaxyMap, &galaxiesPerColumn](
            std::size_t const rowIndex, std::string_view const parsedLine)
        -> void {
        std::size_t galaxyCount{0ULL};
        for (auto const [colIndex, c] : parsedLine | ranges::views::enumerate) {
            if (c == '#') {
                galaxyMap.mGalaxies.emplace_back(colIndex, rowIndex);
                ++galaxiesPerColumn[colIndex];
                ++galaxyCount;
            }
        }
        // check if the row was empty
        if (galaxyCount == 0ULL) {
            galaxyMap.mEmptyRows.emplace_back(rowIndex);
        }
    };
    parseLine(0ULL, line);
    // analyze the other rows
    std::size_t rowIndex{1ULL};
    while (std::getline(fileStream, line)) {
        parseLine(rowIndex, line);
        ++rowIndex;
    }
    // check empty columns
    for (auto const [colIndex, numGalaxies] :
         galaxiesPerColumn | ranges::views::enumerate) {
        if (numGalaxies == 0U) {
            galaxyMap.mEmptyColumns.emplace_back(colIndex);
        }
    }

    return galaxyMap;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const galaxyMap{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_11