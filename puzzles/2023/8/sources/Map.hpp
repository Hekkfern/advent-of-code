#pragma once

#include "Instruction.hpp"
#include "NetworkNode.hpp"
#include <unordered_map>
#include <vector>

namespace aoc_2023_8 {

class Map {
public:
    Map() = default;
    void addInstructions(std::vector<Instruction>&& instructions);
    void addNode(NodeId&& id, NetworkNode&& network);
    uint64_t navigateFromAToZ();

private:
    std::vector<Instruction> mInstructions{};
    std::unordered_map<NodeId, NetworkNode> mNetworkNodes{};
};

} // namespace aoc_2023_8
