#include "solutions.hpp"

#include "State.h"
#include <queue>
#include <unordered_set>
#include <utils/File.hpp>
#include <utils/geometry2d/Coordinate2D.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Grid2D.hpp>

namespace aoc_2023_17 {

// ---------- Private Methods ----------

using HeatLossGrid = utils::geometry2d::Grid2D<uint8_t>;

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

int32_t getLeastHeatLoss(
    HeatLossGrid const& grid, int32_t const minSteps, int32_t const maxSteps)
{
    utils::geometry2d::Coordinate2D<std::size_t> const destination{
        grid.getWidth() - 1ULL, grid.getHeight() - 1ULL};
    utils::geometry2d::Coordinate2D<std::size_t> const origin{0ULL, 0ULL};
    State const startingThroughEast{
        origin, utils::geometry2d::Direction2D::Right, 0, 0};
    State const startingThroughSouth{
        origin, utils::geometry2d::Direction2D::Up, 0, 0};
    std::priority_queue<State, std::vector<State>, CompareStates> pq{
        startingThroughEast, startingThroughSouth};
    std::unordered_set<State> visited{
        startingThroughEast, startingThroughSouth};

    // TODO: https://github.com/keriati/aocpp/blob/main/2023/17/day17.cpp
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    HeatLossGrid const input{parseInput(filePath)};
    return std::to_string(getLeastHeatLoss(input, 1, 3));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    HeatLossGrid const input{parseInput(filePath)};
    return std::to_string(getLeastHeatLoss(input, 4, 10));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_17