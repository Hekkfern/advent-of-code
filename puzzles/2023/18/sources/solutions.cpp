#include "solutions.hpp"

#include "Instruction.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/OrthogonalPolygon2D.h>
#include <utils/geometry2d/Point2D.hpp>
#include <vector>

using namespace utils::geometry2d;

namespace aoc_2023_18 {

// ---------- Private Methods ----------

[[nodiscard]] Direction2D convertToDirectionForPart1(char const c) noexcept
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

[[nodiscard]] Direction2D convertToDirectionForPart2(char const c) noexcept
{
    switch (c) {
    case '0':
        return Direction2D::Right;
    case '1':
        return Direction2D::Down;
    case '2':
        return Direction2D::Left;
    case '3':
        return Direction2D::Up;
    default:
        /* Impossible value */
        assert(false);
    }
}

[[nodiscard]] Instruction
parseInstructionForPart1(std::string_view const line) noexcept
{
    std::stringstream ss{std::string{line}};
    std::string direction;
    uint32_t steps;
    std::string dummy;
    ss >> direction >> steps >> dummy;
    return Instruction{convertToDirectionForPart1(direction[0]), steps};
}

[[nodiscard]] Instruction
parseInstructionForPart2(std::string_view const line) noexcept
{
    std::stringstream ss{std::string{line}};
    std::string dummy;
    std::string colorCodeStr;
    ss >> dummy >> dummy >> colorCodeStr;
    std::string_view colorCode{colorCodeStr};
    return Instruction{
        convertToDirectionForPart2(colorCode.substr(7, 1)[0]),
        *utils::string::toNumber<uint64_t>(colorCode.substr(2, 5), 16)};
}

[[nodiscard]] std::vector<Instruction>
parseInputForPart1(std::filesystem::path const& filePath) noexcept
{
    std::vector<Instruction> instructions;
    bool const result{utils::file::parseAndIterate(
        filePath, [&instructions](std::string_view const line) -> void {
            instructions.emplace_back(parseInstructionForPart1(line));
        })};
    if (!result) {
        return {};
    }
    return instructions;
}

[[nodiscard]] std::vector<Instruction>
parseInputForPart2(std::filesystem::path const& filePath) noexcept
{
    std::vector<Instruction> instructions;
    bool const result{utils::file::parseAndIterate(
        filePath, [&instructions](std::string_view const line) -> void {
            instructions.emplace_back(parseInstructionForPart2(line));
        })};
    if (!result) {
        return {};
    }
    return instructions;
}

std::string solve(std::vector<Instruction> const& instructions)
{
    constexpr Point2D<int64_t> startingPoint{0, 0};
    Point2D<int64_t> currentPoint{startingPoint};
    /* convert instructions into vertexes of a polygon */
    std::vector<Point2D<int64_t>> vertexes{};
    for (auto const& instruction : instructions) {
        auto vec{
            toVector2D<int64_t>(instruction.direction) * instruction.steps};
        currentPoint += vec;
        vertexes.emplace_back(currentPoint);
    }
    /* generate result */
    OrthogonalPolygon2D<int64_t> polygon{vertexes};
    return std::to_string(
        polygon.calculateNumberOfIntrinsicPoints() + polygon.perimeter());
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const instructions{parseInputForPart1(filePath)};
    return solve(instructions);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const instructions{parseInputForPart2(filePath)};
    return solve(instructions);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_18