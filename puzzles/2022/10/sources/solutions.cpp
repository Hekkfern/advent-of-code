#include "solutions.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utils/StringUtils.hpp>
#include <vector>

namespace aoc_2022_10 {

// ---------- Private Methods ----------

const std::unordered_map<std::string, uint32_t> CyclesPerInstruction{
    { "addx", 2U },
    { "noop", 1U }
};

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    int32_t cycleStrengthSum{ 0 };
    uint32_t cycleCounter{ 1U };
    uint32_t registerValue{ 1U };
    constexpr uint32_t InitialCheckpointCycle{ 20U };
    constexpr uint32_t CyclesBetweenCheckpoints{ 40U };
    uint32_t nextCheckpointCycle{ InitialCheckpointCycle };

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        std::string instruction;
        lineStream >> instruction;
        if (((instruction == "addx")
             && ((cycleCounter <= nextCheckpointCycle)
                 && ((cycleCounter + CyclesPerInstruction.at(instruction))
                     > nextCheckpointCycle)))
            || ((instruction == "noop")
                && (cycleCounter == nextCheckpointCycle))) {
            cycleStrengthSum += (nextCheckpointCycle * registerValue);
            nextCheckpointCycle += CyclesBetweenCheckpoints;
        }
        if (instruction == "addx") {
            uint32_t increaseValue = 0;
            lineStream >> increaseValue;
            registerValue += increaseValue;
        }
        cycleCounter += CyclesPerInstruction.at(instruction);
    }

    return std::to_string(cycleStrengthSum);
}

std::string solvePart2(const std::string& filename)
{
    constexpr uint8_t CrtRowLength{ 40U };
    constexpr char LitCrtCharacter{ '#' };
    constexpr char DarkCrtCharacter{ '.' };
    uint32_t registerValue{ 1U };
    uint32_t cycleCounter{ 1U };
    std::ifstream fileStream{ filename };
    std::string line;
    std::vector<std::vector<char>> crtScreen{ {} };
    uint8_t crtScreenRowIndex{ 0U };

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        std::string instruction;
        lineStream >> instruction;
        if (instruction == "addx") {
            // draw
            for (uint8_t i = 0U; i < CyclesPerInstruction.at("addx"); ++i) {
                const bool isLit = ((cycleCounter + i) > (registerValue - 1))
                    || ((cycleCounter + i) > (registerValue + 1));
                crtScreen.at(crtScreenRowIndex)
                    .emplace_back(
                        (isLit) ? (LitCrtCharacter) : (DarkCrtCharacter));
            }
            // modify register
            uint32_t increaseValue = 0;
            lineStream >> increaseValue;
            registerValue += increaseValue;
        } else if (instruction == "addx") {
            // draw
            const bool isLit = (cycleCounter > (registerValue - 1))
                || (cycleCounter > (registerValue + 1));
            crtScreen.at(crtScreenRowIndex)
                .emplace_back((isLit) ? (LitCrtCharacter) : (DarkCrtCharacter));
        }

        cycleCounter += CyclesPerInstruction.at(instruction);
        if (cycleCounter >= CrtRowLength) {
            ++crtScreenRowIndex;
            crtScreen.emplace_back();
        }
    }

    return utils::StringUtils::convertFrom(crtScreen);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_10
