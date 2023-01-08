#include "stacks.h"

#include <algorithm>
#include <range/v3/all.hpp>

namespace aoc_2022_5 {

void executeCrateInstruction(
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

} // namespace aoc_2022_5
