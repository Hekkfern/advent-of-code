#include "solutions.hpp"

#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry3d/OrthogonalLine3D.hpp>
#include <utils/geometry3d/Point3D.hpp>
#include <vector>

namespace aoc_2023_22 {

using namespace utils::geometry3d;
using Brick = utils::geometry3d::OrthogonalLine3D<int32_t>;

// ---------- Private Methods ----------

Brick parseLine(std::string_view const line)
{
    auto const pointListStr{utils::string::split(line, "~")};
    auto const p1Coords{utils::string::split(pointListStr[0], ",")};
    Point3D<int32_t> const p1{
        *utils::string::toNumber<int32_t>(p1Coords[0]),
        *utils::string::toNumber<int32_t>(p1Coords[1]),
        *utils::string::toNumber<int32_t>(p1Coords[2])};
    auto const p2Coords{utils::string::split(pointListStr[1], ",")};
    Point3D<int32_t> const p2{
        *utils::string::toNumber<int32_t>(p2Coords[0]),
        *utils::string::toNumber<int32_t>(p2Coords[1]),
        *utils::string::toNumber<int32_t>(p2Coords[2])};
    return Brick{std::move(p1), std::move(p2)};
}

[[nodiscard]] std::vector<Brick>
parseInput(std::filesystem::path const& filePath) noexcept
{
    std::vector<Brick> output;
    bool const result{utils::file::parseAndIterate(
        filePath, [&output](std::string_view const line) {
            output.emplace_back(parseLine(line));
        })};
    if (!result) {
        return {};
    }
    return output;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto bricks{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_22