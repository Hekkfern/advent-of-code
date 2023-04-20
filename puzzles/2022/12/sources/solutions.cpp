#include "solutions.hpp"

#include "PositionMap.hpp"
#include <fstream>
#include <queue>
#include <range/v3/all.hpp>
#include <unordered_map>
#include <utils/geometry2d/Direction2D.hpp>

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
    std::unordered_map<Point2D<int32_t>, Position> map;
    std::ifstream fileStream{filename};
    std::string line;
    uint32_t rowCounter{0U};
    uint32_t colCounter{0U};
    Position* origin{nullptr};
    Position* destination{nullptr};
    while (std::getline(fileStream, line)) {
        colCounter = 0U;
        for (const auto c : line) {
            Point2D point2D{
                static_cast<int32_t>(colCounter),
                static_cast<int32_t>(rowCounter)};
            auto type{parsePositionType(c)};
            // insert
            auto [insertedItem, isInserted] = map.emplace(
                point2D, Position{std::move(point2D), parseHeight(c), type});
            // detect origin or destination
            switch (type) {
            case PositionType::Origin:
                origin = &insertedItem->second;
                break;
            case PositionType::Destination:
                destination = &insertedItem->second;
                break;
            default:
                /* No statements */
                break;
            }
            ++colCounter;
        }
        ++rowCounter;
    }

    return PositionMap{
        std::move(map), colCounter, rowCounter, *origin, *destination};
}

uint32_t climbHill(PositionMap& positionMap)
{
    // BFS initialization with the starting point
    std::queue<std::pair<Position, uint32_t>> queue;
    queue.emplace(positionMap.getOrigin(), 0U);
    positionMap.setCost(positionMap.getOrigin(), 0U);

    while (!queue.empty()) {
        auto enqueuedItem{queue.front()};
        const auto& enqueuedPosition{enqueuedItem.first};
        const auto enqueuedPositionCost{enqueuedItem.second};
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
            Direction2D::Left};
        for (auto dir : directionsToCheck) {
            if (!positionMap.canMove(
                    enqueuedPosition, dir, ClimbingDirection::Up)) {
                continue;
            }
            auto nextPosition{positionMap.move(enqueuedPosition, dir)};
            // Check if the path due to this movement is not longer than the
            // shortest known path.
            const auto nextCost{enqueuedPositionCost + 1U};
            if ((enqueuedPositionCost + 1U)
                >= positionMap.getCost(nextPosition)) {
                continue;
            }
            queue.emplace(nextPosition, nextCost);
            positionMap.setCost(nextPosition, nextCost);
        }
    }

    // Return the shortest path cost.
    return positionMap.getCost(positionMap.getDestination());
}

uint32_t descendHill(PositionMap& positionMap)
{
    uint32_t bestCost{UINT32_MAX};
    // BFS initialization with the starting point
    std::queue<std::pair<Position, uint32_t>> queue;
    queue.emplace(positionMap.getDestination(), 0U);
    positionMap.setCost(positionMap.getDestination(), 0U);

    while (!queue.empty()) {
        auto enqueuedItem{queue.front()};
        const auto& enqueuedPosition{enqueuedItem.first};
        const auto enqueuedPositionCost{enqueuedItem.second};
        queue.pop();

        // Update best cost
        if (enqueuedPosition.getHeight() == 0U) {
            bestCost = std::min(bestCost, enqueuedPositionCost);
            // This is the end of this path.
            continue;
        }

        // Try to step in each direction:
        static const std::vector<Direction2D> directionsToCheck{
            Direction2D::Up,
            Direction2D::Right,
            Direction2D::Down,
            Direction2D::Left};
        for (auto dir : directionsToCheck) {
            if (!positionMap.canMove(
                    enqueuedPosition, dir, ClimbingDirection::Down)) {
                continue;
            }
            auto nextPosition{positionMap.move(enqueuedPosition, dir)};
            // Check if the path due to this movement is not longer than the
            // shortest known path.
            const auto nextCost{enqueuedPositionCost + 1U};
            if ((enqueuedPositionCost + 1U)
                >= positionMap.getCost(nextPosition)) {
                continue;
            }
            queue.emplace(nextPosition, nextCost);
            positionMap.setCost(nextPosition, nextCost);
        }
    }

    // Return the best path cost.
    return bestCost;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    auto positionMap{parseInput(filename)};
    return std::to_string(climbHill(positionMap));
}

std::string solvePart2(const std::string& filename)
{
    auto positionMap{parseInput(filename)};
    return std::to_string(descendHill(positionMap));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_12