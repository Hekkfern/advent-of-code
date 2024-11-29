#include "solutions.hpp"

#include <range/v3/algorithm/sort.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry3d/OrthogonalLine3D.hpp>
#include <utils/geometry3d/Point3D.hpp>
#include <vector>

namespace aoc_2023_22 {

using Brick = utils::geometry3d::OrthogonalLine3D<>;
using BrickStack = std::vector<Brick>;

constexpr int32_t MinimumHeight{1};

// ---------- Private Methods ----------

/**
 *
 * @param line
 * @return
 */
Brick parseLine(std::string_view const line)
{
    auto const pointListStr{utils::string::split(line, "~")};
    auto const p1Coords{utils::string::split(pointListStr[0], ",")};
    utils::geometry3d::Point3D<> const p1{
        *utils::string::toNumber<int32_t>(p1Coords[0]),
        *utils::string::toNumber<int32_t>(p1Coords[1]),
        *utils::string::toNumber<int32_t>(p1Coords[2])};
    auto const p2Coords{utils::string::split(pointListStr[1], ",")};
    utils::geometry3d::Point3D<> const p2{
        *utils::string::toNumber<int32_t>(p2Coords[0]),
        *utils::string::toNumber<int32_t>(p2Coords[1]),
        *utils::string::toNumber<int32_t>(p2Coords[2])};
    return Brick{std::move(p1), std::move(p2)};
}

/**
 *
 * @param filePath
 * @return
 */
[[nodiscard]] BrickStack
parseInput(std::filesystem::path const& filePath) noexcept
{
    BrickStack output;
    bool const result{utils::file::parseAndIterate(
        filePath, [&output](std::string_view const line) -> void {
            output.emplace_back(parseLine(line));
        })};
    if (!result) {
        return {};
    }
    return output;
}

/**
 *
 * @param brick
 * @return
 */
[[nodiscard]] int32_t findLowestZ(Brick const& brick) noexcept
{
    auto const [vertex1, vertex2]{brick.getVertexes()};
    return std::min(vertex1.getZ(), vertex2.getZ());
}

[[nodiscard]] utils::geometry2d::Point2D<>
convertPoint3DTo2D(utils::geometry3d::Point3D<> const& p) noexcept
{
    return utils::geometry2d::Point2D<>(p.getX(), p.getY());
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto bricks{parseInput(filePath)};
    /* order bricks from lowest to highest height */
    ranges::sort(bricks, [](Brick const& lhs, Brick const& rhs) -> bool {
        return findLowestZ(lhs) < findLowestZ(rhs);
    });
    /* make the bricks fall */
    std::unordered_map<utils::geometry2d::Point2D<>, int32_t> maxHeightMap;
    for (auto& brick : bricks) {
        /* look for maximum height of the brick stack in the positions below
         * this brick */
        int32_t maxHeight{MinimumHeight};
        for (auto const& brickPoint : brick.getPoints()) {
            maxHeight = std::max(
                maxHeight,
                maxHeightMap[convertPoint3DTo2D(brickPoint)] + MinimumHeight);
        }
        /* move the brick to the new height */
        brick.move(
            utils::geometry3d::Vector3D<>{
                0, 0, findLowestZ(brick) - maxHeight + 1});
        /* update the maximum height of the brick stack in the positions below
         * this brick */
        for (auto const& brickPoint : brick.getPoints()) {
            maxHeightMap[convertPoint3DTo2D(brickPoint)] = maxHeight;
        }
    }
    // TODO
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_22
