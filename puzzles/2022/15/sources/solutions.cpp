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

/**
 * @brief      { function_description }
 *
 * @param[in]  line  The line
 *
 * @return     The sensor information.
 */
SensorInfo parseInputLine(std::string const& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))"};
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return SensorInfo{
        Point2D{
            utils::string::toNumber<int32_t>(regexResult[1]),
            utils::string::toNumber<int32_t>(regexResult[2])},
        Point2D{
            utils::string::toNumber<int32_t>(regexResult[3]),
            utils::string::toNumber<int32_t>(regexResult[4])}};
}

/**
 * @brief         { function_description }
 *
 * @param[in,out] multiInterval  The multi interval
 * @param[in]     pairInfo       The pair information
 * @param[in]     goalCoordY     The goal coordinate y
 */
void fillNoBeaconIntervalAtCoordY(
    MultiInterval<int32_t>& multiInterval,
    SensorInfo const& pairInfo,
    int32_t const goalCoordY)
{
    // add all the positions covered by the sensor in the coordinate Y to
    // analyze
    int32_t const distance{static_cast<int32_t>(pairInfo.getDistance())};
    int32_t const diffYAbs{
        std::abs(goalCoordY - pairInfo.getSensorPosition().getY())};
    if (diffYAbs == distance) {
        // add just one value
        int32_t const coordX{pairInfo.getSensorPosition().getX()};
        multiInterval.add(coordX);
    } else if (diffYAbs < distance) {
        // add all the matching nodes
        int32_t const firstPosition{
            pairInfo.getSensorPosition().getX() - (distance - diffYAbs)};
        int32_t const lastPosition{
            pairInfo.getSensorPosition().getX() + (distance - diffYAbs)};
        multiInterval.add(Interval{firstPosition, lastPosition});
    }
}

/**
 * @brief      Calculates the tuning frequency.
 *
 * @param[in]  x     { parameter_description }
 * @param[in]  y     { parameter_description }
 *
 * @return     The tuning frequency.
 */
uint64_t calculateTuningFrequency(int32_t const x, int32_t const y)
{
    return (4000000U * static_cast<uint64_t>(x)) + static_cast<uint64_t>(y);
}

/**
 * @brief      Determines if having beacon possible.
 *
 * @param[in]  sensorList  The sensor list
 * @param[in]  point       The point
 *
 * @return     True if having beacon possible, False otherwise.
 */
bool isHavingBeaconPossible(
    std::vector<SensorInfo> const& sensorList, Point2D<int32_t> const& point)
{
    return ranges::any_of(sensorList, [&point](SensorInfo const& sensor) {
        return sensor.hasBeaconAt(point) || sensor.isCovered(point);
    });
}

/**
 * @brief      { function_description }
 *
 * @param[in]  sensorList  The sensor list
 * @param[in]  gridSize    The grid size
 *
 * @return     { description_of_the_return_value }
 */
Point2D<int32_t>
searchSpace(std::vector<SensorInfo>& sensorList, uint32_t const gridSize)
{
    for (auto& sensor : sensorList) {
        auto currentPosition{sensor.stepAroundOutside()};
        while (currentPosition) {
            auto const& [currentPositionCoordX, currentPositionCoordY]
                = currentPosition->getCoordinates();
            if (currentPositionCoordX >= 0
                && currentPositionCoordX <= static_cast<int32_t>(gridSize)
                && currentPositionCoordY >= 0
                && currentPositionCoordY <= static_cast<int32_t>(gridSize)) {
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
    std::filesystem::path const& filePath,
    std::unordered_map<std::string, std::any>&& extParams)
{
    int32_t const goalCoordY{
        std::any_cast<int32_t>(extParams.at("GoalCoordY"))};
    std::ifstream fileStream{filePath};
    std::string line;
    MultiInterval multiInterval;
    std::unordered_set<Point2D<int32_t>> busyPositions;
    while (std::getline(fileStream, line)) {
        auto pairInfo{parseInputLine(line)};
        if (pairInfo.getSensorPosition().getY() == goalCoordY) {
            busyPositions.emplace(pairInfo.getSensorPosition());
        }
        if (pairInfo.getBeaconPosition().getY() == goalCoordY) {
            busyPositions.emplace(pairInfo.getBeaconPosition());
        }
        fillNoBeaconIntervalAtCoordY(multiInterval, pairInfo, goalCoordY);
    }
    for (auto const& busyPosition : busyPositions) {
        multiInterval.remove(busyPosition.getX());
    }
    return std::to_string(multiInterval.count());
}

std::string solvePart2(
    std::filesystem::path const& filePath,
    std::unordered_map<std::string, std::any>&& extParams)
{
    uint32_t const gridSize{std::any_cast<uint32_t>(extParams.at("GridSize"))};
    std::ifstream fileStream{filePath};
    std::string line;
    std::vector<SensorInfo> sensorList;
    while (std::getline(fileStream, line)) {
        sensorList.emplace_back(parseInputLine(line));
    }
    Point2D const emptySpot{searchSpace(sensorList, gridSize)};
    return std::to_string(
        calculateTuningFrequency(emptySpot.getX(), emptySpot.getY()));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15