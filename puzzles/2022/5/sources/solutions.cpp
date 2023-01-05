#include "solutions.hpp"

#include "stacks.h"

#include <array>
#include <fstream>
#include <sstream>
#include <utils/StringUtils.hpp>

namespace aoc_2022_5 {

constexpr uint32_t NumberOfCrateStacks{ 9U };

using CrateStackList = std::array<CrateStack, NumberOfCrateStacks>;

CrateStackList parseInputStacks(std::ifstream& fileStream)
{
    CrateStackList crateStackList;
    std::string line;
    while (std::getline(fileStream, line)) {
        if (utils::StringUtils::trim(line).empty()) {
            break;
        }
        // todo

    }

    return crateStackList;
}

CraneInstruction parseInputInstruction(const std::string& line)
{
    CraneInstruction craneInstruction{};
    std::stringstream lineStream{ line };
    std::string uselessWord;
    lineStream >> uselessWord >> craneInstruction.mNumCrates >> uselessWord
        >> craneInstruction.mOriginStackId >> uselessWord
        >> craneInstruction.mDestinationStackId;

    return craneInstruction;
}

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    CrateStackList crateStackList = parseInputStacks(fileStream);
    //todo
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

} // namespace aoc_2022_5