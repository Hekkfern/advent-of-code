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

void fillInterval(
    const PairInfo& pairInfo,
    std::vector<MultiInterval>& rowIntervals)
{
    // TODO
}

uint32_t calculateTuningFrequency(const Point2D& point)
{
    return (4000000U * static_cast<uint32_t>(point.getX()))
        + static_cast<uint32_t>(point.getY());
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
    std::vector<MultiInterval> rowIntervals(gridSize);
    while (std::getline(fileStream, line)) {
        auto pairInfo{ parseInputLine(line) };
        fillInterval(pairInfo, rowIntervals);
    }
    // look for the empty spot
    Point2D emptySpot;
    for (auto& rowInterval : rowIntervals) {
        rowInterval = rowInterval.extract(0, gridSize);
        if (rowInterval.count() < gridSize) {
            // empty spot found
            emptySpot = Point2D{ rowInterval.get()[0].getMax() + 1,
                                 rowInterval.get()[1].getMin() - 1 };
        }
    }
    return std::to_string(calculateTuningFrequency(emptySpot));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15