#include "solutions.hpp"

#include "SensorInfo.hpp"
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

SensorInfo parseInputLine(const std::string& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))"
    };
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return SensorInfo{
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
void fillNoBeaconIntervalAtCoordY(
    MultiInterval& multiInterval,
    const SensorInfo& pairInfo,
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

uint32_t calculateTuningFrequency(const int32_t x, const int32_t y)
{
    return (4000000U * static_cast<uint32_t>(x)) + static_cast<uint32_t>(y);
}

bool isHavingBeaconPossible(
    const std::vector<SensorInfo>& sensorList,
    const Point2D& point)
{
    return ranges::any_of(sensorList, [&point](const SensorInfo& sensor) {
        return sensor.hasBeaconAt(point) || sensor.isCovered(point);
    });
}

Point2D searchSpace(
    const std::vector<SensorInfo>& sensorList,
    const uint32_t gridSize)
{
    for (const auto& sensor : sensorList) {
        auto currentPosition{ sensor.stepAroundOutside() };
        while (currentPosition) {
            const auto& [currentPositionCoordX, currentPositionCoordY]
                = currentPosition->getCoordinates();
            if ((currentPositionCoordX >= 0)
                && (currentPositionCoordX <= static_cast<int32_t>(gridSize))
                && (currentPositionCoordY >= 0)
                && (currentPositionCoordY <= static_cast<int32_t>(gridSize))) {
                if (!isHavingBeaconPossible(sensorList, *currentPosition)) {
                    return *currentPosition;
                }
            }

            currentPosition = sensor.stepAroundOutside();
        }
    }

    return Point2D{};
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
        fillNoBeaconIntervalAtCoordY(multiInterval, pairInfo, goalCoordY);
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
    std::vector<SensorInfo> sensorList;
    while (std::getline(fileStream, line)) {
        sensorList.emplace_back(parseInputLine(line));
    }
    const Point2D emptySpot{ searchSpace(sensorList, gridSize) };
    return std::to_string(
        calculateTuningFrequency(emptySpot.getX(), emptySpot.getY()));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15