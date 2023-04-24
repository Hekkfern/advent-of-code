#include "solutions.hpp"

#include "SandMap.hpp"
#include <fstream>
#include <sstream>

namespace aoc_2022_14 {

using namespace utils::geometry2d;

// ---------- Private Methods ----------

SandMap parseInput(std::string const& filename)
{
    SandMap sandMap;
    std::ifstream fileStream{filename};
    std::string line;
    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{line};
        int32_t col{0};
        int32_t row{0};
        char delim{0};
        lineStream >> col >> delim >> row;
        Point2D prevPoint{col, row};
        lineStream >> delim >> delim; // process '->'
        Point2D newPoint{};
        while (lineStream >> col >> delim >> row) {
            newPoint = Point2D{col, row};
            sandMap.addRockLine(prevPoint, newPoint);
            prevPoint = newPoint;
            lineStream >> delim >> delim; // process '->'
        }
    }
    return sandMap;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    SandMap sandMap{parseInput(filename)};
    while (sandMap.addSandGrainInConstrainedSpace()) { }
    return std::to_string(sandMap.getNumberOfSandGrains());
}

std::string solvePart2(std::string const& filename)
{
    SandMap sandMap{parseInput(filename)};
    sandMap.enableInfiniteFloor();
    while (sandMap.addSandGrainInInfiniteSpace()) { }
    return std::to_string(sandMap.getNumberOfSandGrains());
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_14
