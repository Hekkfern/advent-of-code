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
getNextSteps(State const& currentState)
{
    std::vector<std::pair<Coord, Direction2D>> nextSteps;
    auto const& direction{currentState.direction};
    nextSteps.emplace_back(
        currentState.position.move(direction.goStraight()),
        direction.goStraight());
    nextSteps.emplace_back(
        currentState.position.move(direction.turnLeft()),
        direction.turnLeft());
    nextSteps.emplace_back(
        currentState.position.move(direction.turnRight()),
        direction.turnRight());
    return nextSteps;
}

// TODO: https://github.com/keriati/aocpp/blob/main/2023/17/day17.cpp
int32_t getLeastHeatLoss(
    HeatLossGrid const& grid, int32_t const minSteps, int32_t const maxSteps)
{
    Coord const destination{grid.getWidth() - 1ULL, grid.getHeight() - 1ULL};
    Coord const origin{0ULL, 0ULL};
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
            return current.heatLoss;
        }

        std::vector<std::pair<Coord, Direction2D>> nextSteps;
        nextSteps.reserve(3);
    }
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    HeatLossGrid input{parseInput(filePath)};
    input.flipHorizontal();
    return std::to_string(getLeastHeatLoss(input, 1, 3));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    HeatLossGrid const input{parseInput(filePath)};
    return std::to_string(getLeastHeatLoss(input, 4, 10));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_17