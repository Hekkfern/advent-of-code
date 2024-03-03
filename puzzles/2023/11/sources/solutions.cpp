#include "solutions.hpp"

#include "GalaxyMap.hpp"
#include <fstream>
#include <numeric>
#include <range/v3/algorithm/count_if.hpp>
#include <range/v3/view/enumerate.hpp>
#include <utils/Combinations.hpp>
#include <utils/geometry2d/Vector2D.hpp>

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
                galaxyMap.galaxies.emplace_back(colIndex, rowIndex);
                ++galaxiesPerColumn[colIndex];
                ++galaxyCount;
            }
        }
        // check if the row was empty
        if (galaxyCount == 0ULL) {
            galaxyMap.emptyRows.emplace_back(rowIndex);
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
            galaxyMap.emptyColumns.emplace_back(colIndex);
        }
    }
    // sort empty rows and columns
    ranges::sort(galaxyMap.emptyRows);
    ranges::sort(galaxyMap.emptyColumns);

    return galaxyMap;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const galaxyMap{parseInput(filePath)};
    std::vector<std::size_t> galaxyIndexes(galaxyMap.galaxies.size());
    std::iota(galaxyIndexes.begin(), galaxyIndexes.end(), 0ULL);
    uint64_t accumShortestPaths{0ULL};
    utils::combinations::forEachCombination(
        galaxyIndexes,
        2,
        [&galaxyMap, &accumShortestPaths](
            std::vector<std::size_t> const& combination) -> void {
            const auto& galaxy1{galaxyMap.galaxies.at(combination[0])};
            const auto& galaxy2{galaxyMap.galaxies.at(combination[1])};
            const uint64_t distance{
                utils::geometry2d::Vector2D{galaxy1, galaxy2}.distance()};
            const uint64_t numEmptyRows{static_cast<uint64_t>(ranges::count_if(
                galaxyMap.emptyRows,
                [&galaxy1, &galaxy2](const int32_t rowIndex) -> bool {
                    return galaxy1.getY() < rowIndex
                        && rowIndex < galaxy2.getY();
                }))};
            const uint64_t numEmptyCols{static_cast<uint64_t>(ranges::count_if(
                galaxyMap.emptyColumns,
                [&galaxy1, &galaxy2](const int32_t colIndex) -> bool {
                    return galaxy1.getX() < colIndex
                        && colIndex < galaxy2.getX();
                }))};
            accumShortestPaths += distance + numEmptyRows + numEmptyCols;
        });
    return std::to_string(accumShortestPaths);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_11