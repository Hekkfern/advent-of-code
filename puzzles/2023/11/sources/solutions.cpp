#include "solutions.hpp"

#include "GalaxyMap.hpp"
#include <utils/File.hpp>

namespace aoc_2023_11 {

// ---------- Private Methods ----------

GalaxyMap parseInput(std::filesystem::path const& filePath)
{
    GalaxyMap galaxyMap;

    utils::file::parseAndIterateWithIndex(
        filePath,
        [&galaxyMap](
            std::size_t const rowIndex, std::string_view const line) -> void {
            // TODO
        });

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