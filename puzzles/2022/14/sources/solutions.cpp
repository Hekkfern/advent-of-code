#include "solutions.hpp"

#include "SandMap.hpp"
#include <fstream>

namespace aoc_2022_14 {

// ---------- Private Methods ----------

SandMap parseInput(const std::string& filename)
{
    SandMap sandMap;
    std::ifstream fileStream{ filename };
    std::string line;
    while (std::getline(fileStream, line)) {
        // todo
    }
    return sandMap;
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

} // namespace aoc_2022_14