#include "solutions.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/geometry2d/Grid2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_21 {

// ---------- Private Methods ----------

enum class PositionType { GardenPlot, Rock };

using GardenGrid = Grid2D<PositionType>;
using Steps = uint32_t;

PositionType convertToPositionType(char const c) noexcept
{
    switch (c) {
    case '.':
    default:
        return PositionType::GardenPlot;
    case '#':
        return PositionType::Rock;
    }
}

[[nodiscard]] std::pair<GardenGrid, GardenGrid::Coord>
parseInput(std::filesystem::path const& filePath) noexcept
{
    std::vector<std::vector<PositionType>> data;
    GardenGrid::Coord startPosition;
    bool const result{utils::file::parseAndIterate(
        filePath, [&data, &startPosition](std::string_view const line) {
            std::vector<PositionType> row;
            row.reserve(line.size());
            for (char const c : line) {
                if (c == 'S') {
                    startPosition = GardenGrid::Coord{row.size(), data.size()};
                    row.emplace_back(PositionType::GardenPlot);
                } else {
                    row.emplace_back(convertToPositionType(c));
                }
            }
            data.push_back(std::move(row));
        })};
    if (!result) {
        return std::make_pair(GardenGrid{}, GardenGrid::Coord{});
    }
    GardenGrid grid{data};
    grid.flipVertical();
    return std::make_pair(std::move(grid), startPosition);
}

std::vector<GardenGrid::Coord> getNeighbours(
    GardenGrid const& grid, GardenGrid::Coord const& position) noexcept
{
    std::vector<GardenGrid::Coord> neighbourCandidates{
        grid.getCardinalNeighbors(position)};
    return neighbourCandidates
        | ranges::views::
            filter([&grid](GardenGrid::Coord const& candidate) -> bool {
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
    std::unordered_set<GardenGrid::Coord> current;
    std::unordered_set<GardenGrid::Coord> next{startPosition};
    ranges::for_each(ranges::views::iota(0U, maxSteps), [&](uint32_t) -> void {
        current = next;
        next.clear();
        for (auto coord : current) {
            for (auto const& neighbor : getNeighbours(grid, coord)) {
                next.emplace(neighbor);
            }
        }
    });
    return std::to_string(next.size());
}

std::string
solvePart2(std::filesystem::path const& filePath, uint32_t const maxSteps)
{
    // TODO
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21