#include "solutions.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>

namespace aoc_2022_10 {

// ---------- Private Methods ----------

const std::unordered_map<std::string, uint32_t> CyclesPerInstruction{
    { "addx", 2 },
    { "noop", 1 }
};

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    int32_t cycleStrengthSum{ 0 };
    uint32_t cycleCounter{ 0U };
    int32_t registerValue{ 1 };
    constexpr uint32_t InitialCheckpointCycle{ 20U };
    constexpr uint32_t CyclesBetweenCheckpoints{ 40U };
    uint32_t nextCheckpointCycle{ InitialCheckpointCycle };

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        std::string instruction;
        lineStream >> instruction;
        if (((instruction == "addx")
             && ((cycleCounter < nextCheckpointCycle)
                 && ((cycleCounter + CyclesPerInstruction.at(instruction))
                     > nextCheckpointCycle)))
            || ((instruction == "noop")
                && (cycleCounter == nextCheckpointCycle))) {
            cycleStrengthSum
                += (static_cast<int32_t>(cycleCounter) * registerValue);
            nextCheckpointCycle += CyclesBetweenCheckpoints;
        }
        if (instruction == "addx") {
            int32_t increaseValue = 0;
            lineStream >> increaseValue;
            registerValue += increaseValue;
        }
        cycleCounter += CyclesPerInstruction.at(instruction);
    }

    return std::to_string(cycleStrengthSum);
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_10