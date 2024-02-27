#include "Map.hpp"

namespace aoc_2023_8 {

void Map::addInstructions(std::vector<Instruction>&& instructions) noexcept
{
    mInstructions = std::move(instructions);
}

void Map::addNode(NodeId&& id, NetworkNode&& network) noexcept
{
    mNetworkNodes.emplace(id, std::move(network));
}

uint64_t Map::navigateFromAAAToZZZ() const noexcept
{
    constexpr auto InitialNodeId{"AAA"};
    constexpr auto FinalNodeId{"ZZZ"};
    uint32_t instructionIndex{0U};
    uint64_t stepCounter{0ULL};
    NodeId currentNode{InitialNodeId};

    while (currentNode != FinalNodeId) {
        Instruction instruction{mInstructions[instructionIndex]};
        instructionIndex
            = ++instructionIndex >= mInstructions.size() ? 0U : instructionIndex;
        currentNode = mNetworkNodes.at(currentNode).navigate(instruction);
        ++stepCounter;
    }

    return stepCounter;
}

} // namespace aoc_2023_8