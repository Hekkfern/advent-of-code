#include "solutions.hpp"

#include <utils/File.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_21 {

// ---------- Private Methods ----------

enum class PositionType { GardenPlot, Rock };

using GardenGrid = Grid2D<PositionType>;

PositionType convertToPositionType(char const c)
{
    switch (c) {
    case '.':
    default:
        return PositionType::GardenPlot;
    case '#':
        return PositionType::Rock;
    }
}

[[nodiscard]] std::pair<GardenGrid, Coordinate2D<std::size_t>>
parseInput(std::filesystem::path const& filePath)
{
    std::vector<std::vector<PositionType>> data;
    Coordinate2D<std::size_t> startPosition;
    bool const result{utils::file::parseAndIterate(
        filePath, [&data, &startPosition](std::string_view const line) {
            std::vector<PositionType> row;
            row.reserve(line.size());
            for (char const c : line) {
                if (c == 'S') {
                    startPosition = Coordinate2D<std::size_t>{
                        row.size(), data.size()};
                    row.emplace_back(PositionType::GardenPlot);
                } else {
                    row.emplace_back(convertToPositionType(c));
                }
            }
            data.push_back(std::move(row));
        })};
    if (!result) {
        return std::make_pair(GardenGrid{}, Coordinate2D<std::size_t>{});
    }
    return std::make_pair(GardenGrid{data}, startPosition);
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string
solvePart1(std::filesystem::path const& filePath, uint32_t const maxSteps)
{
    auto const [grid, startPosition]{parseInput(filePath)};
    (void)maxSteps;
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21