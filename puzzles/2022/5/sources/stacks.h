#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2022_5 {

using StackId = uint32_t;

struct CraneInstruction {
    uint32_t mNumCrates;
    StackId mOriginStackIndex;
    StackId mDestinationStackIndex;
};

using CrateStack = std::vector<char>; // where index 0 means the bottom of the
                                      // stack

void executeCrateInstruction(
    std::vector<CrateStack>& crateStackList,
    const CraneInstruction& craneInstruction);

} // namespace aoc_2022_5
