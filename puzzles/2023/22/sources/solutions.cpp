#include "solutions.hpp"

#include <range/v3/algorithm/sort.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry3d/OrthogonalLine3D.hpp>
#include <utils/geometry3d/Point3D.hpp>
#include <vector>

namespace aoc_2023_22 {

constexpr int32_t MinimumHeight{1};

// ---------- Private Methods ----------

struct Brick {
    utils::geometry3d::OrthogonalLine3D<> mLine;
    std::vector<Brick*> mSupportedBy{};
};

using BrickStack = std::vector<Brick>;

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
    return Brick{
        utils::geometry3d::OrthogonalLine3D<>{std::move(p1), std::move(p2)}};
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
    auto const [vertex1, vertex2]{brick.mLine.getVertexes()};
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
    std::unordered_map<utils::geometry2d::Point2D<>, std::pair<int32_t, Brick*>>
        maxHeightMap;
    for (auto& brick : bricks) {
        /* look for maximum height of the brick stack in the positions below
         * this brick */
        int32_t maxHeight{MinimumHeight};
        std::vector<std::pair<int32_t, Brick*>> willLandOn;
        for (auto const& brickPoint : brick.mLine.getPoints()) {
            auto const& valueInMap{
                maxHeightMap[convertPoint3DTo2D(brickPoint)]};
            int32_t const highestHeightInMap{valueInMap.first + 1};
            if (maxHeight < highestHeightInMap) {
                maxHeight = highestHeightInMap;
                willLandOn = {valueInMap.second};
            } else if (maxHeight == highestHeightInMap) {
                willLandOn.emplace_back(valueInMap.second);
            }
        }
        /* move the brick to the new height */
        brick.mLine.move(
            utils::geometry3d::Vector3D<>{
                0, 0, maxHeight - findLowestZ(brick)});
        /* update the maximum height of the brick stack in the positions below
         * this brick */
        for (auto const& brickPoint : brick.mLine.getPoints()) {
            auto& valueInMap{maxHeightMap[convertPoint3DTo2D(brickPoint)]};
            valueInMap.first = maxHeight;
            //TODO
        }
        /* update the list of bricks supporting this brick */
        brick.mSupportedBy = std::move(willLandOn);
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
