#include "Map.hpp"

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/transform.hpp>
#include <utils/Math.hpp>

namespace aoc_2023_8 {

void Map::addInstructions(std::vector<Instruction>&& instructions) noexcept
{
    mInstructions = std::move(instructions);
}

void Map::addNode(NodeId&& id, NetworkNode&& network) noexcept
{
    mNetworkNodes.emplace(id, std::move(network));
}

Instruction Map::yieldInstruction(uint32_t& instructionIndex) const noexcept
{
    Instruction instruction{mInstructions[instructionIndex]};
    instructionIndex
        = ++instructionIndex >= mInstructions.size() ? 0U : instructionIndex;
    return instruction;
}

uint64_t Map::navigateFromAAAToZZZ() const noexcept
{
    static constexpr auto InitialNodeId{"AAA"};
    static constexpr auto FinalNodeId{"ZZZ"};
    uint32_t instructionIndex{0U};
    uint64_t stepCounter{0ULL};
    NodeId currentNode{InitialNodeId};

    while (currentNode != FinalNodeId) {
        Instruction const instruction{yieldInstruction(instructionIndex)};
        currentNode = mNetworkNodes.at(currentNode).navigate(instruction);
        ++stepCounter;
    }

    return stepCounter;
}

uint64_t Map::navigateFromAllXXAToAllXXZ() const noexcept
{
    static constexpr auto isFinalNode{[](NodeId const& nodeId) -> bool {
        return nodeId[2] == 'Z';
    }};

    // look for starting nodes
    auto const initialNodeIds{
        mNetworkNodes | ranges::views::keys
        | ranges::views::filter([](NodeId const& nodeId) -> bool {
              return nodeId[2] == 'A';
          })
        | ranges::to<std::vector>};

    uint64_t stepResult{1ULL};
    uint32_t instructionIndex{0U};
    for (NodeId const& initialNodeId : initialNodeIds) {
        uint64_t stepCounter{0ULL};
        NodeId currentNode{initialNodeId};
        while (!isFinalNode(currentNode)) {
            Instruction const instruction{yieldInstruction(instructionIndex)};
            currentNode = mNetworkNodes.at(currentNode).navigate(instruction);
            ++stepCounter;
        }
        stepResult = utils::math::lcm(stepResult, stepCounter);
    }

    return stepResult;
}

} // namespace aoc_2023_8
