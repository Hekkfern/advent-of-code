#include "solutions.hpp"

#include "InstructionType.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utils/StringUtils.hpp>
#include <vector>

namespace aoc_2022_10 {

// ---------- Private Methods ----------

constexpr char LitCrtCharacter{ '#' };
constexpr char DarkCrtCharacter{ '.' };
constexpr uint8_t CrtRowLength{ 40U };

const std::unordered_map<std::string, uint32_t> CyclesPerInstruction{
    { AddxInstructionName, 2U },
    { NoopInstructionName, 1U }
};

void draw(
    std::vector<std::vector<char>>& crtScreen,
    uint8_t rowIndex,
    uint32_t cycleCounter,
    uint32_t registerValue)
{
    const bool isLit = (cycleCounter > (registerValue - 1))
        || (cycleCounter > (registerValue + 1));
    crtScreen.at(rowIndex).emplace_back(
        (isLit) ? (LitCrtCharacter) : (DarkCrtCharacter));
}

void moveCrtPointer(
    uint32_t& cycleCounter,
    std::vector<std::vector<char>>& crtScreen,
    uint8_t& crtScreenRowIndex)
{
    ++cycleCounter;
    if (cycleCounter % CrtRowLength == 0) {
        ++crtScreenRowIndex;
        crtScreen.emplace_back();
    }
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::string line;
    uint32_t cycleStrengthSum{ 0U };
    uint32_t cycleCounter{ 1U };
    uint32_t registerValue{ 1U };
    constexpr uint32_t InitialCheckpointCycle{ 20U };
    constexpr uint32_t CyclesBetweenCheckpoints{ 40U };
    uint32_t nextCheckpointCycle{ InitialCheckpointCycle };

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        std::string instruction;
        lineStream >> instruction;
        if (((instruction == AddxInstructionName)
             && ((cycleCounter <= nextCheckpointCycle)
                 && ((cycleCounter + CyclesPerInstruction.at(instruction))
                     > nextCheckpointCycle)))
            || ((instruction == NoopInstructionName)
                && (cycleCounter == nextCheckpointCycle))) {
            cycleStrengthSum += (nextCheckpointCycle * registerValue);
            nextCheckpointCycle += CyclesBetweenCheckpoints;
        }
        if (instruction == AddxInstructionName) {
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
    uint32_t registerValue{ 1U };
    uint32_t cycleCounter{ 1U };
    std::ifstream fileStream{ filename };
    std::string line;
    std::vector<std::vector<char>> crtScreen{ {} };
    uint8_t crtScreenRowIndex{ 0U };

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{ line };
        std::string instructionText;
        lineStream >> instructionText;
        const InstructionType instruction{ convertInstructionType(
            instructionText) };
        switch (instruction) {
        case InstructionType::ADDX: {
            // draw
            for (uint8_t i = 0U;
                 i < CyclesPerInstruction.at(AddxInstructionName);
                 ++i) {
                draw(
                    crtScreen,
                    crtScreenRowIndex,
                    cycleCounter + i,
                    registerValue);
                moveCrtPointer(cycleCounter, crtScreen, crtScreenRowIndex);
            }
            // modify register
            uint32_t increaseValue = 0;
            lineStream >> increaseValue;
            registerValue += increaseValue;
            break;
        }
        case InstructionType::NOOP: {
            draw(crtScreen, crtScreenRowIndex, cycleCounter, registerValue);
            moveCrtPointer(cycleCounter, crtScreen, crtScreenRowIndex);
            break;
        }
        default: {
            /* NO STATEMENTS */
            break;
        }
        }
    }

    return utils::StringUtils::convertFrom(crtScreen);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_10
