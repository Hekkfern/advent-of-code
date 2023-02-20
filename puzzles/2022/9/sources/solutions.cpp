#include "solutions.hpp"

#include "Rope.hpp"
#include "RopeInstruction.hpp"
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <utils/String.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_9 {

using namespace utils::geometry2d;

// ---------- Private Methods ----------

Direction2D convertDirectionCharacter(char directionChar)
{
    Direction2D result = Direction2D::Up;
    switch (directionChar) {
    case 'U':
        result = Direction2D::Up;
        break;
    case 'D':
        result = Direction2D::Down;
        break;
    case 'L':
        result = Direction2D::Left;
        break;
    case 'R':
        result = Direction2D::Right;
        break;
    default:
        /* No reachable */
        break;
    }
    return result;
}

RopeInstruction parseInputLine(const std::string& line)
{
    std::stringstream lineStream{ line };
    char directionChar = 0;
    std::string numberPositions;
    lineStream >> directionChar >> numberPositions;
    return RopeInstruction{ convertDirectionCharacter(directionChar),
                            utils::string::toNumber<uint32_t>(
                                numberPositions) };
}

struct Position2DHash {
    size_t operator()(const Point2D& position) const
    {
        return std::hash<int32_t>{}(position.getX())
            ^ std::hash<int32_t>{}(position.getY());
    }
};

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    constexpr uint32_t RopeLength{ 2U };

    std::ifstream fileStream{ filename };
    std::string line;
    Rope<RopeLength> rope;
    std::unordered_set<Point2D, Position2DHash> visitedTailPositions;

    while (std::getline(fileStream, line)) {
        const auto instruction = parseInputLine(line);
        for (uint32_t i = 0U; i < instruction.mQuantity; ++i) {
            rope.moveHead(instruction.mDirection);
            visitedTailPositions.emplace(rope.getTailPosition());
        }
    }

    return std::to_string(visitedTailPositions.size());
}

std::string solvePart2(const std::string& filename)
{
    constexpr uint32_t RopeLength{ 10U };

    std::ifstream fileStream{ filename };
    std::string line;
    Rope<RopeLength> rope;
    std::unordered_set<Point2D, Position2DHash> visitedTailPositions;

    while (std::getline(fileStream, line)) {
        const auto instruction = parseInputLine(line);
        for (uint32_t i = 0U; i < instruction.mQuantity; ++i) {
            rope.moveHead(instruction.mDirection);
            visitedTailPositions.emplace(rope.getTailPosition());
        }
    }

    return std::to_string(visitedTailPositions.size());
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_9
