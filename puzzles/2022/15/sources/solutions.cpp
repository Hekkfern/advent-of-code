#include "solutions.hpp"

#include "PairInfo.hpp"
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <unordered_map>
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
 * @param[in,out] interval
 * @param[in] sensorBeaconPair
 */
void fillNoBeaconInterval(
    utils::interval::MultiInterval& interval,
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
        interval.add(coordX);
    } else if (diffYAbs < distance) {
        // add all the matching nodes
        const int32_t firstPosition{ pairInfo.getSensorPosition().getX()
                                     - (distance - diffYAbs) };
        const int32_t lastPosition{ pairInfo.getSensorPosition().getX()
                                    + (distance - diffYAbs) };
        interval.add(Interval{ firstPosition, lastPosition });
    }
}

uint32_t calculateTuningFrequency(int32_t x, int32_t y)
{
    return (4000000U * static_cast<uint32_t>(x)) + static_cast<uint32_t>(y);
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
    utils::interval::MultiInterval interval;
    while (std::getline(fileStream, line)) {
        auto pairInfo{ parseInputLine(line) };
        fillNoBeaconInterval(interval, pairInfo, goalCoordY);
    }
    return std::to_string(ranges::accumulate(
        interval.get(),
        0U,
        [](uint32_t sum, const utils::interval::Interval& interval) {
            return sum + interval.length();
        }));
}

std::string solvePart2(
    const std::string& filename,
    std::unordered_map<std::string, std::any>&& extParams)
{
    //    const int32_t gridSize{
    //    std::any_cast<int32_t>(extParams.at("GridSize")) }; std::ifstream
    //    fileStream{ filename }; std::string line; while
    //    (std::getline(fileStream, line)) {
    //        auto pairInfo{ parseInputLine(line) };
    //    }
    //    return std::to_string(calculateTuningFrequency(1, 1));
    (void)filename;
    (void)extParams;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15