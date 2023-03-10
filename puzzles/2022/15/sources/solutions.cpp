#include "solutions.hpp"

#include <fstream>
#include <regex>
#include <utils/String.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_15 {

using namespace utils::geometry2d;

// ---------- Private Methods ----------

std::pair<Point2D, Point2D> parseInputLine(const std::string& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))"
    };
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return std::make_pair(
        Point2D{ utils::string::toNumber<int32_t>(regexResult[1]),
                 utils::string::toNumber<int32_t>(regexResult[2]) },
        Point2D{ utils::string::toNumber<int32_t>(regexResult[3]),
                 utils::string::toNumber<int32_t>(regexResult[4]) });
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    (void)filename;
    return "";
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_15