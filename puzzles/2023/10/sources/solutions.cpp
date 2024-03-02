#include "solutions.hpp"

#include "PipeType.hpp"
#include <cassert>
#include <range/v3/view/enumerate.hpp>
#include <unordered_map>
#include <utils/File.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2023_10 {

/* note: vertical coord is inverted because the input is parsed from top (row=0)
 * to bottom (row=N) */
std::unordered_map<
    PipeType,
    std::pair<Vector2D<int32_t>, Vector2D<int32_t>>> const PipeTranslation{
    {PipeType::SouthEast, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{1, 0}}},
    {PipeType::Horizontal, {Vector2D<int32_t>{-1, 0}, Vector2D<int32_t>{1, 0}}},
    {PipeType::NorthWest, {Vector2D<int32_t>{0, -1}, Vector2D<int32_t>{-1, 0}}},
    {PipeType::Vertical, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{0, -1}}},
    {PipeType::NorthEast, {Vector2D<int32_t>{0, -1}, Vector2D<int32_t>{1, 0}}},
    {PipeType::SouthWest, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{-1, 0}}}};

// ---------- Private Methods ----------

PipeType parsePipeType(char const c)
{
    switch (c) {
    case 'F':
        return PipeType::SouthEast;
    case '-':
        return PipeType::Horizontal;
    case 'J':
        return PipeType::NorthWest;
    case '|':
        return PipeType::Vertical;
    case 'L':
        return PipeType::NorthEast;
    case '7':
        return PipeType::SouthWest;
    case '.':
        return PipeType::None;
    case 'S':
        return PipeType::Start;
    default:
        assert(false);
    }
}

/* where Field[row][col] and row==0 is the top row of the input file */
using Field = std::vector<std::vector<PipeType>>;

std::pair<Field, Point2D<int32_t>>
parseInput(std::filesystem::path const& filePath)
{
    Field outList;
    Point2D<int32_t> startingPoint;

    utils::file::parseAndIterateWithIndex(
        filePath,
        [&outList, &startingPoint](
            std::size_t const rowIndex, std::string_view const line) -> void {
            std::vector<PipeType> row;
            row.reserve(line.size());
            for (auto const [colIndex, c] : line | ranges::views::enumerate) {
                row.emplace_back(parsePipeType(c));
                if (c == 'S') {
                    startingPoint = Point2D<int32_t>::create(
                        colIndex, rowIndex);
                }
            }
            outList.emplace_back(std::move(row));
        });

    return std::make_pair(outList, startingPoint);
}

PipeType
getTypeForPosition(Field const& field, int32_t const row, int32_t const col)
{
    return field.at(static_cast<std::size_t>(row))
        .at(static_cast<std::size_t>(col));
}

Point2D<int32_t> move(
    Field const& field,
    Point2D<int32_t> const& pipePosition,
    Point2D<int32_t> const& previousPosition)
{
    auto const translation{PipeTranslation.at(
        getTypeForPosition(field, pipePosition.getY(), pipePosition.getX()))};
    if (pipePosition + translation.first == previousPosition) {
        return pipePosition + translation.second;
    } else {
        return pipePosition + translation.first;
    }
}

Point2D<int32_t>
getStartingNeighbor(Field const& field, Point2D<int32_t> const& start)
{
    Point2D<int32_t> result;
    for (auto const& neighbor : start.getNeighbors()) {
        auto const translation{PipeTranslation.at(
            getTypeForPosition(field, neighbor.getY(), neighbor.getX()))};
        if ((neighbor + translation.first) == start
            || (neighbor + translation.second) == start) {
            return neighbor;
        }
    }
    // no reachable code
    return start;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const [field, start]{parseInput(filePath)};
    // look for two pipes connected to the start
    auto currentPosition{getStartingNeighbor(field, start)};
    auto previousPosition{start};
    // count nodes in loop
    std::size_t count{1ULL};
    while (currentPosition != start) {
        auto nextPosition = move(field, currentPosition, previousPosition);
        previousPosition = currentPosition;
        currentPosition = nextPosition;
        ++count;
    }
    return std::to_string(count / 2);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const [field, start]{parseInput(filePath)};
    // look for two pipes connected to the start
    auto currentPosition{getStartingNeighbor(field, start)};
    auto previousPosition{start};
    // get nodes of the loop
    std::vector<Point2D<int32_t>> points{start};
    while (currentPosition != start) {
        auto nextPosition = move(field, currentPosition, previousPosition);
        previousPosition = currentPosition;
        currentPosition = nextPosition;
        points.emplace_back(previousPosition);
    }
    return std::to_string(
        calculateNumberOfIntrinsicPointsInsidePolygon(points));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_10
