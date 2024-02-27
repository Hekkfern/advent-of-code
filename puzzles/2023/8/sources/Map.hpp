#pragma once

#include "Instruction.hpp"
#include "NetworkNode.hpp"
#include <unordered_map>
#include <vector>

namespace aoc_2023_8 {

class Map {
public:
    Map() = default;
    void addInstructions(std::vector<Instruction>&& instructions) noexcept;
    void addNode(NodeId&& id, NetworkNode&& network) noexcept;
    [[nodiscard]] uint64_t navigateFromAToZ() const noexcept;

private:
    std::vector<Instruction> mInstructions{};
    std::unordered_map<NodeId, NetworkNode> mNetworkNodes{};
};

} // namespace aoc_2023_8
