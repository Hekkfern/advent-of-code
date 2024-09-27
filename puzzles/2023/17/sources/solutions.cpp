#include "solutions.hpp"

#include "Node.h"
#include "State.h"
#include <queue>
#include <unordered_map>
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
    std::unordered_map<Node, uint32_t> best;

    // Helper that adds a given state to the queue if it is better than our best
    // known for that position, direction and remaining steps
    auto push_if_better = [&best, &pq](State const& s) {
        Node const node{s.position, s.direction, s.steps};
        if (not best.contains(node) || best[node] > s.heatLoss) {
            best[node] = s.heatLoss;
            pq.push(s);
        }
    };

    /* Two starting states, {0,0}, going right and down. Note that steps == 0
    and heat_loss == 0 */
    push_if_better(startingThroughEast);
    push_if_better(startingThroughSouth);

    while (not pq.empty()) {
        State const current{pq.top()};
        /* If we are at our destination, report the heat_loss, because of the
         * priority queue we have a guarantee this is the minimum value */
        if (current.position == destination) {
            return current.heatLoss;
        }
        pq.pop();

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

            push_if_better(nextState);
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
    HeatLossGrid input{parseInput(filePath)};
    input.flipVertical();
    return std::to_string(getLeastHeatLoss(input, 4, 10));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_17