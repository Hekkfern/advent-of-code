#include "solutions.hpp"

#include <utils/File.hpp>
#include <utils/geometry2d/Grid2D.hpp>

namespace aoc_2023_17 {

// ---------- Private Methods ----------

using HeatLossGrid = utils::geometry2d::Grid2D<uint8_t>;

constexpr int32_t MaxStraightLineLength{3};

HeatLossGrid parseInput(std::filesystem::path const& filePath)
{
    auto const data{*utils::file::readMatrixOfDigits(filePath)};
    return HeatLossGrid{data};
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

} // namespace aoc_2023_17