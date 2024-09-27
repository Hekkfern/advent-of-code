#include "solutions.hpp"

#include "State.h"
#include <queue>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>
#include <vector>

namespace aoc_2023_17 {

using namespace utils::geometry2d;
using Coord = Coordinate2D<std::size_t>;

// ---------- Private Methods ----------

using HeatLossGrid = Grid2D<uint8_t>;

HeatLossGrid parseInput(std::filesystem::path const& filePath)
{
    auto const data{*utils::file::readMatrixOfDigits(filePath)};
    return HeatLossGrid{data};
}

struct CompareStates {
    bool operator()(State const& a, State const& b) const
    {
        return a.heatLoss > b.heatLoss;
    }
};

std::vector<std::pair<Coord, Direction2D>>
getNextSteps(HeatLossGrid const& grid, State const& currentState)
{
    std::vector<std::pair<Coord, Direction2D>> nextSteps;
    nextSteps.reserve(3);
    /* straight movement */
    auto straightDirection{currentState.direction.goStraight()};
    auto straightMovement{grid.move(currentState.position, straightDirection)};
    if (straightMovement) {
        nextSteps.emplace_back(*straightMovement, straightDirection);
    }
    /* turn-left movement */
    auto turnLeftDirection{currentState.direction.turnLeft()};
    auto turnLeftMovement{grid.move(currentState.position, turnLeftDirection)};
    if (turnLeftMovement) {
        nextSteps.emplace_back(*turnLeftMovement, turnLeftDirection);
    }
    /* turn-right movement */
    auto turnRightDirection{currentState.direction.turnRight()};
    auto turnRightMovement{
        grid.move(currentState.position, turnRightDirection)};
    if (turnRightMovement) {
        nextSteps.emplace_back(*turnRightMovement, turnRightDirection);
    }
    return nextSteps;
}

// TODO: https://github.com/keriati/aocpp/blob/main/2023/17/day17.cpp
uint32_t getLeastHeatLoss(
    HeatLossGrid const& grid, uint8_t const minSteps, uint8_t const maxSteps)
{
    Coord const destination{grid.getWidth() - 1ULL, 0ULL};
    Coord const origin{0ULL, grid.getHeight() - 1ULL};
    State const startingThroughEast{origin, Direction2D::Right, 0, 0};
    State const startingThroughSouth{origin, Direction2D::Down, 0, 0};
    std::priority_queue<State, std::vector<State>, CompareStates> pq{};
    pq.push(startingThroughEast);
    pq.push(startingThroughSouth);
    std::unordered_set<State> visited{
        startingThroughEast, startingThroughSouth};

    while (!pq.empty()) {
        State const current{pq.top()};
        pq.pop();

        if (current.position == destination) {
            if (current.steps < minSteps) {
                continue;
            };
            return current.heatLoss;
        }

        std::vector<std::pair<Coord, Direction2D>> nextSteps{
            getNextSteps(grid, current)};

        for (auto const& nextStep : nextSteps) {
            if (current.steps > (maxSteps - 1)
                && current.direction == nextStep.second) {
                continue;
            }
            if (current.steps < minSteps
                && current.direction != nextStep.second) {
                continue;
            }

            State nextState{
                nextStep.first,
                nextStep.second,
                current.direction == nextStep.second ? current.steps + 1U : 1U,
                current.heatLoss + grid.at(nextStep.first)};

            if (!visited.contains(nextState)) {
                pq.push(nextState);
                visited.insert(nextState);
            }
        }
    }
    return 0U;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    HeatLossGrid input{parseInput(filePath)};
    input.flipVertical();
    return std::to_string(getLeastHeatLoss(input, 1, 3));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    HeatLossGrid const input{parseInput(filePath)};
    input.flipVertical();
    return std::to_string(getLeastHeatLoss(input, 4, 10));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_17