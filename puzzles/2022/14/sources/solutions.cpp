#include "solutions.hpp"

#include "SandMap.hpp"
#include <fstream>
#include <sstream>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2022_14 {

using namespace utils::geometry2d;

// ---------- Private Methods ----------

const Vector2D sandFalling{ Direction2D{ Direction2D::Up }.toVector2D() };
const Vector2D sandSlidingLeft{
    Direction2D{ Direction2D::UpLeft }.toVector2D()
};
const Vector2D sandSlidingRight{
    Direction2D{ Direction2D::UpRight }.toVector2D()
};

SandMap parseInput(const std::string& filename)
{
    SandMap sandMap;
    std::ifstream fileStream{ filename };
    std::string line;
    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        int32_t col{ 0 };
        int32_t row{ 0 };
        char delim;
        lineStream >> col >> delim >> row;
        Point2D prevPoint{ col, row };
        Point2D newPoint{};
        while (lineStream >> col >> delim >> row) {
            newPoint = Point2D{ col, row };
            sandMap.addRockLine(prevPoint, newPoint);
        }
        prevPoint = newPoint;
        lineStream >> delim >> delim; // process '->'
    }
    return sandMap;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    SandMap sandMap{ parseInput(filename) };
    while (sandMap.addSandGrain()) { }
    return std::to_string(sandMap.getNumberOfSandGrains());
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_14