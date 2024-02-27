#include "Map.hpp"

namespace aoc_2023_8 {

void Map::addInstructions(std::vector<Instruction>&& instructions)
{
    mInstructions = std::move(instructions);
}

void Map::addNode(NodeId&& id, NetworkNode&& network)
{
    mNetworkNodes.emplace(id, std::move(network));
}

uint64_t Map::navigateFromAToZ()
{
    // TODO
    return 1;
}

} // namespace aoc_2023_8