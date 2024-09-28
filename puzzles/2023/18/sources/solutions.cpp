#include "solutions.hpp"

#include "Instruction.h"
#include <sstream>
#include <string>
#include <utils/File.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Polygon2D.h>
#include <vector>

using namespace utils::geometry2d;

namespace aoc_2023_18 {

// ---------- Private Methods ----------

Direction2D convertToDirection(char const c)
{
    switch (c) {
    case 'R':
        return Direction2D::Right;
    case 'D':
        return Direction2D::Down;
    case 'L':
        return Direction2D::Left;
    case 'U':
        return Direction2D::Up;
    default:
        /* Impossible value */
        assert(false);
    }
}

Instruction parseInstruction(std::string_view const line)
{
    std::stringstream ss{std::string{line}};
    std::string direction;
    uint32_t steps;
    std::string colorCode;
    ss >> direction >> steps >> colorCode;
    return Instruction{
        convertToDirection(direction[0]), steps, colorCode.substr(2, 6)};
}

std::vector<Instruction> parseInput(std::filesystem::path const& filePath)
{
    std::vector<Instruction> instructions;
    bool const result{utils::file::parseAndIterate(
        filePath, [&instructions](std::string_view const line) {
            instructions.emplace_back(parseInstruction(line));
        })};
    if (!result) {
        return {};
    }
    return instructions;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const instructions{parseInput(filePath)};
    constexpr Point2D<> startingPoint{0, 0};
    Point2D<> currentPoint{startingPoint};
    std::vector<Point2D<>> vertexes{startingPoint};
    for (auto const& instruction : instructions) {
        auto vec{toVector2D(instruction.direction)};
    }
    Polygon2D<> polygon{vertexes};
    return std::to_string(polygon.area());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_18