#include "solutions.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/geometry2d/Grid2D.hpp>
#include <utils/geometry2d/InfiniteGrid2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_21 {

// ---------- Private Methods ----------

enum class PositionType { GardenPlot, Rock };

using Garden1Grid = Grid2D<PositionType>;
using Garden2Grid = InfiniteGrid2D<PositionType>;
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

[[nodiscard]] std::pair<Garden1Grid, Garden1Grid::Coord>
parseInputForPart1(std::filesystem::path const& filePath) noexcept
{
    std::vector<std::vector<PositionType>> data;
    Garden1Grid::Coord startPosition;
    bool const result{utils::file::parseAndIterate(
        filePath, [&data, &startPosition](std::string_view const line) {
            std::vector<PositionType> row;
            row.reserve(line.size());
            for (char const c : line) {
                if (c == 'S') {
                    startPosition = Garden1Grid::Coord{row.size(), data.size()};
                    row.emplace_back(PositionType::GardenPlot);
                } else {
                    row.emplace_back(convertToPositionType(c));
                }
            }
            data.push_back(std::move(row));
        })};
    if (!result) {
        return std::make_pair(Garden1Grid{}, Garden1Grid::Coord{});
    }
    Garden1Grid grid{data};
    grid.flipVertical();
    return std::make_pair(std::move(grid), startPosition);
}

[[nodiscard]] std::pair<Garden2Grid, Garden2Grid::Coord>
parseInputForPart2(std::filesystem::path const& filePath) noexcept
{
    std::vector<std::vector<PositionType>> data;
    Garden2Grid::Coord startPosition;
    bool const result{utils::file::parseAndIterate(
        filePath, [&data, &startPosition](std::string_view const line) {
            std::vector<PositionType> row;
            row.reserve(line.size());
            for (char const c : line) {
                if (c == 'S') {
                    startPosition = Garden2Grid::Coord{
                        static_cast<int64_t>(row.size()),
                        static_cast<int64_t>(data.size())};
                    row.emplace_back(PositionType::GardenPlot);
                } else {
                    row.emplace_back(convertToPositionType(c));
                }
            }
            data.push_back(std::move(row));
        })};
    if (!result) {
        return std::make_pair(Garden2Grid{}, Garden2Grid::Coord{});
    }
    Garden2Grid grid{data};
    grid.flipVertical();
    return std::make_pair(std::move(grid), startPosition);
}

std::vector<Garden1Grid::Coord> getNeighboursForPart1(
    Garden1Grid const& grid, Garden1Grid::Coord const& position) noexcept
{
    std::vector<Garden1Grid::Coord> neighbourCandidates{
        grid.getCardinalNeighbors(position)};
    return neighbourCandidates
        | ranges::views::
            filter([&grid](Garden1Grid::Coord const& candidate) -> bool {
                return grid.at(candidate) == PositionType::GardenPlot;
            })
        | ranges::to<std::vector>;
}

std::vector<Garden2Grid::Coord> getNeighboursForPart2(
    Garden2Grid const& grid, Garden2Grid::Coord const& position) noexcept
{
    std::vector<Garden2Grid::Coord> neighbourCandidates{
        grid.getCardinalNeighbors(position)};
    return neighbourCandidates
        | ranges::views::
            filter([&grid](Garden2Grid::Coord const& candidate) -> bool {
                return grid.at(candidate) == PositionType::GardenPlot;
            })
        | ranges::to<std::vector>;
}

uint64_t calculateNumberOfPlotsForPart2(
    Garden2Grid const& grid,
    Garden2Grid::Coord const& startPosition,
    uint64_t maxSteps) noexcept
{
    std::unordered_set<Garden2Grid::Coord> current;
    std::unordered_set<Garden2Grid::Coord> next{startPosition};
    ranges::for_each(ranges::views::iota(0U, maxSteps), [&](uint32_t) -> void {
        current = next;
        next.clear();
        for (auto coord : current) {
            for (auto const& neighbor : getNeighboursForPart2(grid, coord)) {
                next.emplace(neighbor);
            }
        }
    });
    return next.size();
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string
solvePart1(std::filesystem::path const& filePath, Steps const maxSteps)
{
    auto const [grid, startPosition]{parseInputForPart1(filePath)};
    /* analyze the garden */
    std::unordered_set<Garden1Grid::Coord> current;
    std::unordered_set<Garden1Grid::Coord> next{startPosition};
    ranges::for_each(ranges::views::iota(0U, maxSteps), [&](uint32_t) -> void {
        current = next;
        next.clear();
        for (auto coord : current) {
            for (auto const& neighbor : getNeighboursForPart1(grid, coord)) {
                next.emplace(neighbor);
            }
        }
    });
    return std::to_string(next.size());
}

std::string
solvePart2(std::filesystem::path const& filePath, uint32_t const maxSteps)
{
    auto const [grid, startPosition]{parseInputForPart2(filePath)};
    auto const x0{calculateNumberOfPlotsForPart2(grid, startPosition, 65)};
    auto const x1{calculateNumberOfPlotsForPart2(grid, startPosition, 131 + 65)};
    auto const x2{calculateNumberOfPlotsForPart2(grid, startPosition, 131 * 2 + 65)};
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21