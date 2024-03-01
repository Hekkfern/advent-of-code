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

std::unordered_map<
    PipeType,
    std::pair<Vector2D<int32_t>, Vector2D<int32_t>>> const PipeTranslation{
    {PipeType::SouthEast, {Vector2D<int32_t>{0, -1}, Vector2D<int32_t>{1, 0}}},
    {PipeType::Horizontal, {Vector2D<int32_t>{-1, 0}, Vector2D<int32_t>{1, 0}}},
    {PipeType::NorthWest, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{-1, 0}}},
    {PipeType::Vertical, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{0, -1}}},
    {PipeType::NorthEast, {Vector2D<int32_t>{0, 1}, Vector2D<int32_t>{1, 0}}},
    {PipeType::SouthWest,
     {Vector2D<int32_t>{0, -1}, Vector2D<int32_t>{-1, 0}}}};

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

using Field = std::vector<std::vector<PipeType>>;

std::pair<Field, Point2D<int32_t>>
parseInput(std::filesystem::path const& filePath)
{
    Field outList;
    Point2D<int32_t> startingPoint;

    utils::file::parseAndIterateWithIndex(
        filePath,
        [&outList, &startingPoint](
            std::size_t const rowIndex, std::string_view const line) {
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

Point2D<int32_t> move(
    Point2D<int32_t> const& pipePosition,
    PipeType const pipeType,
    Point2D<int32_t> const& previousPosition)
{
    auto const translation{PipeTranslation.at(pipeType)};
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
            field.at(static_cast<std::size_t>(neighbor.getX()))
                .at(static_cast<std::size_t>(neighbor.getY())))};
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
    std::size_t count{0ULL};
    while (currentPosition != start) {
        auto const pipeType{
            field.at(static_cast<std::size_t>(currentPosition.getX()))
                .at(static_cast<std::size_t>(currentPosition.getY()))};
        auto nextPosition = move(currentPosition, pipeType, previousPosition);
        previousPosition = currentPosition;
        currentPosition = nextPosition;
        ++count;
    }
    return std::to_string(count);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const [field, start]{parseInput(filePath)};
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_10
