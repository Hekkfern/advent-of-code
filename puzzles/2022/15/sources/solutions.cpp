#include "solutions.hpp"

#include "Node.h"
#include "PairInfo.h"
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <unordered_map>
#include <utils/String.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_15 {

using namespace utils::geometry2d;

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

constexpr int32_t GoalCoordY{ 10 };

void addOccupiedPosition(
    std::unordered_map<int32_t, Node>& nodeList,
    const Point2D& position,
    const NodeType type)
{
    if (position.getY() == GoalCoordY) {
        const int32_t sensorCoordX{ position.getX() };
        auto sensorIt{ nodeList.find(sensorCoordX) };
        if (sensorIt != std::end(nodeList)) {
            sensorIt->second.setType(type);
        } else {
            nodeList.emplace(sensorCoordX, Node(sensorCoordX, type));
        }
    }
}

/**
 * @brief
 * @param[in,out] nodeList
 * @param[in] sensorBeaconPair
 */
void fillNoBeaconList(
    std::unordered_map<int32_t, Node>& nodeList,
    const PairInfo& pairInfo)
{
    // add sensor and/or beacon if they are in the coordinate Y to analyze
    addOccupiedPosition(
        nodeList, pairInfo.getSensorPosition(), NodeType::Sensor);
    addOccupiedPosition(
        nodeList, pairInfo.getBeaconPosition(), NodeType::Beacon);

    // add all the positions covered by the sensor in the coordinate Y to
    // analyze
    const int32_t distance{ static_cast<int32_t>(pairInfo.getDistance()) };
    const int32_t diffYAbs{ std::abs(
        GoalCoordY - pairInfo.getSensorPosition().getY()) };
    if (diffYAbs == distance) {
        // add just one node
        const int32_t coordX{ pairInfo.getSensorPosition().getX() };
        if (!nodeList.contains(coordX)) {
            nodeList.emplace(coordX, Node{ coordX, NodeType::Empty });
        }
    } else if (diffYAbs < distance) {
        // add all the matching nodes
        const int32_t firstPosition{ pairInfo.getBeaconPosition().getX()
                                     - (distance - diffYAbs) };
        const int32_t lastPosition{ pairInfo.getBeaconPosition().getX()
                                    + (distance - diffYAbs) };
        for (int32_t coordX = firstPosition; coordX <= lastPosition; ++coordX) {
            if (!nodeList.contains(coordX)) {
                nodeList.emplace(coordX, Node{ coordX, NodeType::Empty });
            }
        }
    }
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    std::unordered_map<int32_t, Node> nodeList;
    while (std::getline(fileStream, line)) {
        auto pairInfo{ parseInputLine(line) };
        fillNoBeaconList(nodeList, pairInfo);
    }
    return std::to_string(
        ranges::count_if(nodeList, [](const std::pair<int32_t, Node>& node) {
            return node.second.getType() == NodeType::Empty;
        }));
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15