#include "solutions.hpp"

#include "PositionMap.hpp"
#include <fstream>
#include <range/v3/all.hpp>
#include <vector>
#include <queue>

namespace aoc_2022_12 {

// ---------- Private Methods ----------

Height parseHeight(const char c)
{
    if (c == 'S') {
        return 0;
    }
    if (c == 'E') {
        return 'z' - 'a';
    }
    return static_cast<Height>(c - 'a');
}

PositionType parsePositionType(const char c)
{
    if (c == 'S') {
        return PositionType::Origin;
    }
    if (c == 'E') {
        return PositionType::Destination;
    }
    return PositionType::Normal;
}

PositionMap parseInput(const std::string& filename)
{
    std::vector<std::vector<Position>> positionMap;
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t rowCounter{ 0U };
    while (std::getline(fileStream, line)) {
        positionMap.emplace_back(); // add new row
        uint32_t itemCounter{ 0U };
        for (const auto c : line) {
            Point2D point2D{ static_cast<int32_t>(itemCounter),
                             static_cast<int32_t>(rowCounter) };
            positionMap.at(rowCounter)
                .emplace_back(
                    std::move(point2D), parseHeight(c), parsePositionType(c));
        }
    }
    ranges::reverse(positionMap);
    return positionMap;
}

void climbHill(const PositionMap& positionMap){
    std::queue<Position> queue;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    auto positionMap{ parseInput(filename) };

}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_12