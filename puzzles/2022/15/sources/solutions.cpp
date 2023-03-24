#include "solutions.hpp"

#include "PairInfo.hpp"
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <utils/Interval.hpp>
#include <utils/MultiInterval.hpp>
#include <utils/String.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_15 {

using namespace utils::geometry2d;
using namespace utils::interval;

// ---------- Private Methods ----------

PairInfo parseInputLine(const std::string& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))"
    };
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return PairInfo{
        Point2D{ utils::string::toNumber<int32_t>(regexResult[1]),
                 utils::string::toNumber<int32_t>(regexResult[2]) },
        Point2D{ utils::string::toNumber<int32_t>(regexResult[3]),
                 utils::string::toNumber<int32_t>(regexResult[4]) }
    };
}

/**
 * @brief
 * @param[in,out] multiInterval
 * @param[in] sensorBeaconPair
 */
void fillNoBeaconInterval(
    MultiInterval& multiInterval,
    const PairInfo& pairInfo,
    const int32_t goalCoordY)
{
    // add all the positions covered by the sensor in the coordinate Y to
    // analyze
    const int32_t distance{ static_cast<int32_t>(pairInfo.getDistance()) };
    const int32_t diffYAbs{ std::abs(
        goalCoordY - pairInfo.getSensorPosition().getY()) };
    if (diffYAbs == distance) {
        // add just one value
        const int32_t coordX{ pairInfo.getSensorPosition().getX() };
        multiInterval.add(coordX);
    } else if (diffYAbs < distance) {
        // add all the matching nodes
        const int32_t firstPosition{ pairInfo.getSensorPosition().getX()
                                     - (distance - diffYAbs) };
        const int32_t lastPosition{ pairInfo.getSensorPosition().getX()
                                    + (distance - diffYAbs) };
        multiInterval.add(Interval{ firstPosition, lastPosition });
    }
}

void addToGrid(
    MultiInterval& multiInterval,
    const int32_t value,
    const int32_t amplitude,
    const int32_t maximum)
{
    multiInterval.add(Interval{ std::clamp(value - amplitude, 0, maximum),
                                std::clamp(value + amplitude, 0, maximum) });
}

void fillGrid(
    const PairInfo& pairInfo,
    std::vector<MultiInterval>& rowIntervals,
    const uint32_t gridSize)
{
    const int32_t maxX{ static_cast<int32_t>(gridSize) };
    const int32_t initialRowIndex{ pairInfo.getSensorPosition().getY()
                                   - static_cast<int32_t>(
                                       pairInfo.getDistance()) };
    const int32_t middleRowIndex{ pairInfo.getSensorPosition().getY() };
    const int32_t finalRowIndex{ pairInfo.getSensorPosition().getY()
                                 + static_cast<int32_t>(
                                     pairInfo.getDistance()) };
    for (int32_t rowIndex{ initialRowIndex }; rowIndex <= middleRowIndex;
         ++rowIndex) {
        if (rowIndex < 0) {
            continue;
        }
        if (rowIndex > maxX) {
            break;
        }
        const int32_t amplitude{ rowIndex - initialRowIndex };
        addToGrid(
            rowIntervals[rowIndex],
            pairInfo.getSensorPosition().getX(),
            amplitude,
            maxX);
    }
    for (int32_t rowIndex{ middleRowIndex + 1 }; rowIndex <= finalRowIndex;
         ++rowIndex) {
        if (rowIndex < 0) {
            continue;
        }
        if (rowIndex > maxX) {
            break;
        }
        const int32_t amplitude{ static_cast<int32_t>(pairInfo.getDistance())
                                 - (rowIndex - middleRowIndex) };
        addToGrid(
            rowIntervals[rowIndex],
            pairInfo.getSensorPosition().getX(),
            amplitude,
            maxX);
    }
}

uint32_t calculateTuningFrequency(const std::pair<int32_t, int32_t>& coords)
{
    return (4000000U * static_cast<uint32_t>(coords.first))
        + static_cast<uint32_t>(coords.second);
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(
    const std::string& filename,
    std::unordered_map<std::string, std::any>&& extParams)
{
    const int32_t goalCoordY{ std::any_cast<int32_t>(
        extParams.at("GoalCoordY")) };
    std::ifstream fileStream{ filename };
    std::string line;
    MultiInterval multiInterval;
    std::unordered_set<Point2D> busyPositions;
    while (std::getline(fileStream, line)) {
        auto pairInfo{ parseInputLine(line) };
        if (pairInfo.getSensorPosition().getY() == goalCoordY) {
            busyPositions.emplace(pairInfo.getSensorPosition());
        }
        if (pairInfo.getBeaconPosition().getY() == goalCoordY) {
            busyPositions.emplace(pairInfo.getBeaconPosition());
        }
        fillNoBeaconInterval(multiInterval, pairInfo, goalCoordY);
    }
    for (const auto& busyPosition : busyPositions) {
        multiInterval.remove(busyPosition.getX());
    }
    return std::to_string(multiInterval.count());
}

std::string solvePart2(
    const std::string& filename,
    std::unordered_map<std::string, std::any>&& extParams)
{
    const uint32_t gridSize{ std::any_cast<uint32_t>(
        extParams.at("GridSize")) };
    std::ifstream fileStream{ filename };
    std::string line;
    std::vector<MultiInterval> rowIntervals(gridSize + 1);
    while (std::getline(fileStream, line)) {
        auto pairInfo{ parseInputLine(line) };
        fillGrid(pairInfo, rowIntervals, gridSize);
    }
    // look for the empty spot
    std::pair<int32_t, int32_t> emptySpotCoords;
    for (uint32_t rowIndex{ 0U }; rowIndex < rowIntervals.size(); ++rowIndex) {
        // look for the only row that has two intervals (which means there is a
        // gap, i.e., the empty spot)
        if (rowIntervals[rowIndex].get().size() > 1) {
            // empty spot found
            int32_t coordY{ static_cast<int32_t>(rowIndex) };
            int32_t coordX{ rowIntervals[rowIndex].get().at(0).getMax() + 1 };
            emptySpotCoords = std::make_pair(coordX, coordY);
            break;
        }
    }
    return std::to_string(calculateTuningFrequency(emptySpotCoords));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15