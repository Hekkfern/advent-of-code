#include "solutions.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <utils/File.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_21 {

// ---------- Private Methods ----------

enum class PositionType { GardenPlot, Rock };

using GardenGrid = Grid2D<PositionType>;
using Steps = uint32_t;

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
    GardenGrid grid{data};
    grid.flipVertical();
    return std::make_pair(std::move(grid), startPosition);
}

std::vector<Coordinate2D<std::size_t>>
getNeighbours(GardenGrid const& grid, Coordinate2D<std::size_t> const& position)
{
    std::vector<Coordinate2D<std::size_t>> neighbourCandidates{
        grid.getCardinalNeighbors(position)};
    return neighbourCandidates
        | ranges::views::
            filter([&grid](Coordinate2D<std::size_t> const& candidate) -> bool {
                return grid.at(candidate) == PositionType::GardenPlot;
            })
        | ranges::to<std::vector>;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string
solvePart1(std::filesystem::path const& filePath, Steps const maxSteps)
{
    auto const [grid, startPosition]{parseInput(filePath)};
    /* analyze the garden */
    std::unordered_map<Coordinate2D<std::size_t>, Steps> visited{
        {startPosition, 0}};
    for (auto const step : ranges::views::iota(0ULL, maxSteps)) {
        for (
            auto const visitedPosition :
            visited
                | ranges::views::filter(
                    [step](std::pair<Coordinate2D<std::size_t>, Steps> const&
                               item) -> bool { return item.second == step; })) {

        }
    }
    return std::to_string(visited.size());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21