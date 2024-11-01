#include "solutions.hpp"

#include <queue>
#include <range/v3/algorithm/fold_left.hpp>
#include <unordered_map>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/extensions/ContainerTools.hpp>
#include <utils/geometry2d/Grid2D.hpp>
#include <utils/geometry2d/InfiniteGrid2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_21 {

// ---------- Private Methods ----------

enum class PositionType { GardenPlot, Rock };

using Garden1Grid = Grid2D<PositionType>;
using Garden2Grid = InfiniteGrid2D<PositionType>;
using Steps = uint64_t;

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

uint64_t calculateNumberOfPlotsForPart1(
    Garden1Grid const& grid,
    Garden1Grid::Coord const& startPosition,
    uint64_t const maxSteps) noexcept
{
    std::unordered_map<Steps, uint64_t> stepsToPlots;
    std::unordered_set<Garden1Grid::Coord> visited;
    std::queue<std::pair<Garden1Grid::Coord, Steps>> queue;
    queue.emplace(startPosition, 0);
    auto current = utils::extensions::try_take_front(queue);
    while (current) {
        auto const [position, steps]{*current};
        if (steps <= maxSteps && not visited.contains(position)) {
            stepsToPlots[steps] += 1;
            visited.emplace(position);
            for (
                auto const& neighbour : getNeighboursForPart1(grid, position)) {
                queue.emplace(neighbour, steps + 1);
            }
        }
        /* get next */
        current = utils::extensions::try_take_front(queue);
    }
    return ranges::fold_left(
        stepsToPlots,
        0ULL,
        [maxSteps](uint64_t const acc, std::pair<Steps, uint64_t> const& pair) {
            return acc + (pair.first % 2 == maxSteps % 2 ? pair.second : 0);
        });
}

uint64_t calculateNumberOfPlotsForPart2(
    Garden2Grid const& grid,
    Garden2Grid::Coord const& startPosition,
    uint64_t const maxSteps) noexcept
{
    std::unordered_map<Steps, uint64_t> stepsToPlots;
    std::unordered_set<Garden2Grid::Coord> visited;
    std::queue<std::pair<Garden2Grid::Coord, Steps>> queue;
    queue.emplace(startPosition, 0);
    auto current = utils::extensions::try_take_front(queue);
    while (current) {
        auto const [position, steps]{*current};
        if (steps <= maxSteps && not visited.contains(position)) {
            stepsToPlots[steps] += 1;
            visited.emplace(position);
            for (
                auto const& neighbour : getNeighboursForPart2(grid, position)) {
                queue.emplace(neighbour, steps + 1);
            }
        }
        /* get next */
        current = utils::extensions::try_take_front(queue);
    }
    return ranges::fold_left(
        stepsToPlots,
        0ULL,
        [maxSteps](uint64_t const acc, std::pair<Steps, uint64_t> const& pair) {
            return acc + (pair.first % 2 == maxSteps % 2 ? pair.second : 0);
        });
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
    auto const result{
        calculateNumberOfPlotsForPart1(grid, startPosition, maxSteps)};
    return std::to_string(result);
}

std::string
solvePart2(std::filesystem::path const& filePath, Steps const maxSteps)
{
    auto const [grid, startPosition]{parseInputForPart2(filePath)};
    int64_t const fullSize{static_cast<int64_t>(grid.getBaseWidth())};
    int64_t const edgeSize{fullSize / 2};
    auto const y0{calculateNumberOfPlotsForPart2(grid, startPosition, 65)};
    auto const y1{
        calculateNumberOfPlotsForPart2(grid, startPosition, 65 + 131)};
    auto const y2{
        calculateNumberOfPlotsForPart2(grid, startPosition, 65 + (2 * 131))};
    auto const coefficients{solveQuadraticSystem(y0, y1, y2)};
    int64_t const maxRounds = (static_cast<int64_t>(maxSteps) - edgeSize)
        / fullSize;
    return std::to_string(
        coefficients[0] + coefficients[1] * maxRounds
        + coefficients[2] * maxRounds * maxRounds);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_21