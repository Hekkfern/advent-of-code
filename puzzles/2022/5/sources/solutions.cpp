#include "solutions.hpp"

#include <fstream>
#include <range/v3/all.hpp>
#include <vector>

namespace aoc_2022_5 {

// ---------- Private types ----------

using StackId = uint32_t;

struct CraneInstruction {
    uint32_t mNumCrates;
    StackId mOriginStackIndex;
    StackId mDestinationStackIndex;
};

using CrateStack = std::vector<char>; // where index 0 means the bottom of the
                                      // stack

// ---------- Private Methods ----------

std::vector<CrateStack> parseInputStacks(std::ifstream& fileStream)
{
    std::vector<CrateStack> crateStackList;

    std::string line;
    bool done = false;
    // process input line-by-line
    while (!done && std::getline(fileStream, line)) {
        // scan each line, char-by-char
        for (size_t i = 0; i < line.length(); ++i) {
            // if there is a digit in the input, this is terminal line
            if (std::isdigit(line[i]) != 0) {
                done = true;
                break;
            }
            // if it's not an upper-case letter, skip over it
            if (std::isupper(line[i]) == 0) {
                continue;
            }
            // calculate the destination stack
            const size_t stack = (i - 1) / 4;
            // and insert
            if (crateStackList.size() <= stack) {
                crateStackList.resize(stack + 1);
            }
            crateStackList[stack].push_back(line[i]);
        }
    }
    // flip all the vectors, so we have the top character in the highest index
    ranges::for_each(crateStackList, ranges::reverse);
    // eat the empty-line after the initial state
    std::getline(fileStream, line);

    return crateStackList;
}

CraneInstruction parseInputInstruction(const std::string& line)
{
    CraneInstruction craneInstruction{};
    std::stringstream lineStream{ line };
    std::string uselessWord;
    lineStream >> uselessWord >> craneInstruction.mNumCrates >> uselessWord
        >> craneInstruction.mOriginStackIndex >> uselessWord
        >> craneInstruction.mDestinationStackIndex;
    --craneInstruction.mOriginStackIndex; // zero-base
    --craneInstruction.mDestinationStackIndex; // zero-base

    return craneInstruction;
}

std::string generateResult(const std::vector<CrateStack>& crateStackList)
{
    std::string result;

    for (const auto& crate : crateStackList) {
        if (crate.empty()) {
            continue;
        }
        result += crate.back();
    }

    return result;
}

void executeCrateMover9000Instruction(
    std::vector<CrateStack>& crateStackList,
    const CraneInstruction& craneInstruction)
{
    auto& originStack = crateStackList[craneInstruction.mOriginStackIndex];
    // view of the last elements of the stack, in reverse order
    auto originStackView = originStack | ranges::views::reverse
        | ranges::views::take(craneInstruction.mNumCrates);
    // copy to the end of the other stack
    ranges::copy(
        originStackView,
        std::back_inserter(
            crateStackList[craneInstruction.mDestinationStackIndex]));
    // remove the last elements of the origin stack
    originStack.resize(originStack.size() - craneInstruction.mNumCrates);
}

void executeCrateMover9001Instruction(
    std::vector<CrateStack>& crateStackList,
    const CraneInstruction& craneInstruction)
{
    auto& originStack = crateStackList[craneInstruction.mOriginStackIndex];
    // view of the last elements of the stack, in order
    auto originStackView = originStack | ranges::views::reverse
        | ranges::views::take(craneInstruction.mNumCrates)
        | ranges::views::reverse;
    // copy to the end of the other stack
    ranges::copy(
        originStackView,
        std::back_inserter(
            crateStackList[craneInstruction.mDestinationStackIndex]));
    // remove the last elements of the origin stack
    originStack.resize(originStack.size() - craneInstruction.mNumCrates);
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::vector<CrateStack> crateStackList = parseInputStacks(fileStream);
    std::string line;
    while (std::getline(fileStream, line)) {
        const CraneInstruction craneInstruction = parseInputInstruction(line);
        executeCrateMover9000Instruction(crateStackList, craneInstruction);
    }
    return generateResult(crateStackList);
}

std::string solvePart2(const std::string& filename)
{
    std::ifstream fileStream{ filename };
    std::vector<CrateStack> crateStackList = parseInputStacks(fileStream);
    std::string line;
    while (std::getline(fileStream, line)) {
        const CraneInstruction craneInstruction = parseInputInstruction(line);
        executeCrateMover9001Instruction(crateStackList, craneInstruction);
    }
    return generateResult(crateStackList);
}

// ---------- End of Private Methods ----------

} // namespace aoc_2022_5
