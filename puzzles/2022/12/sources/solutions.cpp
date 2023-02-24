#include "solutions.hpp"

#include "PositionMap.hpp"
#include <fstream>
#include <queue>
#include <range/v3/all.hpp>
#include <unordered_map>
#include <utils/geometry2d/Direction2D.hpp>
#include <vector>

namespace aoc_2022_12 {

// ---------- Private Methods ----------

Height parseHeight(const char c)
{
    if (c == 'S') {
        return 0;
    }
    if (c == 'E') {
        return 'z' - 'a';
    }
    return static_cast<Height>(c - 'a');
}

PositionType parsePositionType(const char c)
{
    if (c == 'S') {
        return PositionType::Origin;
    }
    if (c == 'E') {
        return PositionType::Destination;
    }
    return PositionType::Normal;
}

PositionMap parseInput(const std::string& filename)
{
    std::vector<std::vector<Position>> positionMap;
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t rowCounter{ 0U };
    while (std::getline(fileStream, line)) {
        positionMap.emplace_back(); // add new row
        uint32_t itemCounter{ 0U };
        for (const auto c : line) {
            Point2D point2D{ static_cast<int32_t>(itemCounter),
                             static_cast<int32_t>(rowCounter) };
            positionMap.at(rowCounter)
                .emplace_back(
                    std::move(point2D), parseHeight(c), parsePositionType(c));
        }
        ++rowCounter;
    }
    ranges::reverse(positionMap);
    return positionMap;
}

uint32_t climbHill(PositionMap& positionMap)
{
    // BFS initialization with the starting point
    std::queue<std::pair<Position, uint32_t>> queue;
    queue.emplace(positionMap.getOrigin(), 0U);
    positionMap.setCost(positionMap.getOrigin(), 0U);

    while (!queue.empty()) {
        auto [enqueuedPosition, enqueuedPositionCost]{ queue.front() };
        queue.pop();

        // Do not explore past end
        if (enqueuedPosition.getType() == PositionType::Destination) {
            continue;
        }

        // Try to step in each direction:
        static const std::vector<Direction2D> directionsToCheck{
            Direction2D::Up,
            Direction2D::Right,
            Direction2D::Down,
            Direction2D::Left
        };
        for (auto dir : directionsToCheck) {
            if (!positionMap.canMove(enqueuedPosition, dir)) {
                continue;
            }
            // Check if the path due to this movement is not longer than the
            // shortest known path.
            if ((enqueuedPositionCost + 1U)
                >= positionMap.getCost(enqueuedPosition)) {
                continue;
            }

            auto nextPosition{ enqueuedPosition + dir };
            queue.emplace(nextPosition, enqueuedPositionCost + 1U);
            positionMap.setCost(nextPosition, enqueuedPositionCost + 1U);
        }
    }

    // Return the shortest path cost.
    return positionMap.getCost(positionMap.getDestination());
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    auto positionMap{ parseInput(filename) };
    return std::to_string(climbHill(positionMap));
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_12