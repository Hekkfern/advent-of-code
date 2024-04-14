#include "solutions.hpp"

#include <utils/File.hpp>
#include <utils/geometry2d/Grid2D.hpp>

namespace aoc_2023_16 {

// ---------- Private Methods ----------

/**
 * @brief      Parses the whole input file and generates a flatten grid.
 *
 * @param[in]  filePath  The path to the input file.
 *
 * @return     Parsed data.
 */
utils::geometry2d::Grid2D<char>
parseInput(std::filesystem::path const& filePath)
{
    auto const data{*utils::file::readMatrixOfChars(filePath)};
    return utils::geometry2d::Grid2D<char>{data};
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

} // namespace aoc_2023_16