#include "Map.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/transform.hpp>

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
    constexpr auto InitialNodeId{"AAA"};
    constexpr auto FinalNodeId{"ZZZ"};
    uint32_t instructionIndex{0U};
    uint64_t stepCounter{0ULL};
    NodeId currentNode{InitialNodeId};

    while (currentNode != FinalNodeId) {
        Instruction instruction{yieldInstruction(instructionIndex)};
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
    static constexpr auto areAllNodesFinal{
        [](std::vector<NodeId> const& nodeIds) -> bool {
            return ranges::all_of(nodeIds, isFinalNode);
        }};

    // look for starting nodes
    auto initialNodeIds{
        mNetworkNodes | ranges::views::keys
        | ranges::views::filter([](NodeId const& nodeId) -> bool {
              return nodeId[2] == 'A';
          })
        | ranges::to<std::vector>};

    uint32_t instructionIndex{0U};
    uint64_t stepCounter{0ULL};
    std::vector<NodeId> currentNodes{initialNodeIds};

    while (!areAllNodesFinal(currentNodes)) {
        Instruction instruction{yieldInstruction(instructionIndex)};
        currentNodes
            = currentNodes
            | ranges::views::
                transform([this, instruction](NodeId const& nodeId) -> NodeId {
                    return mNetworkNodes.at(nodeId).navigate(instruction);
                })
            | ranges::to<std::vector>;
        ++stepCounter;
    }

    return stepCounter;
}

} // namespace aoc_2023_8