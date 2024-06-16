#include "solutions.hpp"

#include <queue>
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

struct State {
    State(
        utils::geometry2d::Coordinate2D<std::size_t> const& position,
        utils::geometry2d::Direction2D const& direction,
        int32_t const steps,
        int32_t const heatLoss)
        : position(position)
        , direction(direction)
        , steps(steps)
        , heatLoss(heatLoss)
    {
    }

    utils::geometry2d::Coordinate2D<std::size_t> position;
    utils::geometry2d::Direction2D direction;
    int32_t steps;
    int32_t heatLoss;
};

struct CompareStates {
    bool operator()(State const& a, State const& b) const
    {
        return a.heatLoss > b.heatLoss;
    }
};

int32_t getLeastHeatLoss(
    HeatLossGrid const& grid, int32_t const minSteps, int32_t const maxSteps)
{

    std::priority_queue<State, std::vector<State>, CompareStates> pq;

    // TODO
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_17