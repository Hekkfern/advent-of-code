#include "solutions.hpp"

#include "InstructionType.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utils/String.hpp>
#include <vector>

namespace aoc_2022_10 {

// ---------- Private Methods ----------

constexpr char LitCrtCharacter{'#'};
constexpr char DarkCrtCharacter{'.'};
constexpr uint8_t CrtRowLength{40U};

std::unordered_map<std::string, uint32_t> const CyclesPerInstruction{
    {AddxInstructionName, 2U}, {NoopInstructionName, 1U}};

void draw(
    std::vector<std::vector<char>>& crtScreen,
    uint8_t rowIndex,
    uint32_t crtPixelPosition,
    uint32_t registerValue)
{
    bool const isLit = (crtPixelPosition >= (registerValue - 1))
        && (crtPixelPosition <= (registerValue + 1));
    crtScreen.at(rowIndex).emplace_back(
        (isLit) ? (LitCrtCharacter) : (DarkCrtCharacter));
}

void moveCrtPointer(
    uint32_t& crtPixelPosition,
    std::vector<std::vector<char>>& crtScreen,
    uint8_t& crtScreenRowIndex)
{
    ++crtPixelPosition;
    if (crtPixelPosition % CrtRowLength == 0) {
        ++crtScreenRowIndex;
        crtPixelPosition = 0;
        crtScreen.emplace_back();
    }
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::ifstream fileStream{filePath};
    std::string line;
    uint32_t cycleStrengthSum{0U};
    uint32_t cycleCounter{1U};
    uint32_t registerValue{1U};
    constexpr uint32_t InitialCheckpointCycle{20U};
    constexpr uint32_t CyclesBetweenCheckpoints{40U};
    uint32_t nextCheckpointCycle{InitialCheckpointCycle};

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{line};
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

std::string solvePart2(std::filesystem::path const& filePath)
{
    uint32_t registerValue{1U};
    uint32_t crtPixelPosition{0U};
    std::ifstream fileStream{filePath};
    std::string line;
    std::vector<std::vector<char>> crtScreen{{}};
    uint8_t crtScreenRowIndex{0U};

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream{line};
        std::string instructionText;
        lineStream >> instructionText;
        InstructionType const instruction{
            convertInstructionType(instructionText)};
        switch (instruction) {
        case InstructionType::ADDX: {
            // draw
            for (uint8_t i = 0U;
                 i < CyclesPerInstruction.at(AddxInstructionName);
                 ++i) {
                draw(
                    crtScreen,
                    crtScreenRowIndex,
                    crtPixelPosition,
                    registerValue);
                moveCrtPointer(crtPixelPosition, crtScreen, crtScreenRowIndex);
            }
            // modify register based on value provided by addx instruction
            uint32_t increaseValue = 0;
            lineStream >> increaseValue;
            registerValue += increaseValue;
            break;
        }
        case InstructionType::NOOP: {
            draw(crtScreen, crtScreenRowIndex, crtPixelPosition, registerValue);
            moveCrtPointer(crtPixelPosition, crtScreen, crtScreenRowIndex);
            break;
        }
        default: {
            /* NO STATEMENTS */
            break;
        }
        }
    }
    crtScreen.pop_back();

    return utils::string::convertFrom(crtScreen);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_10
