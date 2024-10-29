#include "solutions.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/Math.hpp>
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
    uint64_t rounds) noexcept
{
    int64_t const fullSize{static_cast<int64_t>(grid.getBaseWidth())};
    int64_t const edgeSize{fullSize / 2};
    std::unordered_set<Garden2Grid::Coord> current;
    std::unordered_set<Garden2Grid::Coord> next{startPosition};
    auto const maxSteps{edgeSize + fullSize * rounds};
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

/**
 * @brief Solves the quadratic system of equations.
 *
 * @param y0 Value of the function at x = 0.
 * @param y1 Value of the function at x = 1.
 * @param y2 Value of the function at x = 2.
 *
 * @return Coefficients of the quadratic equation, from lowest to highest power.
 */
std::array<uint64_t, 3>
solveQuadraticSystem(uint64_t const y0, uint64_t const y1, uint64_t const y2)
{
    uint64_t const a{(y2 - (2 * y1) + y0) / 2};
    uint64_t const b{y1 - y0 - a};
    uint64_t const c{y0};
    return {c, b, a};
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
    int64_t const fullSize{static_cast<int64_t>(grid.getBaseWidth())};
    int64_t const edgeSize{fullSize / 2};
    auto const y0{calculateNumberOfPlotsForPart2(grid, startPosition, 0)};
    auto const y1{calculateNumberOfPlotsForPart2(grid, startPosition, 1)};
    auto const y2{calculateNumberOfPlotsForPart2(grid, startPosition, 2)};
    auto const coefficients{solveQuadraticSystem(y0, y1, y2)};
    int64_t const maxRounds = (maxSteps - edgeSize) / fullSize;
    return std::to_string(
        coefficients[0] + coefficients[1] * maxRounds
        + coefficients[2] * maxRounds * maxRounds);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21