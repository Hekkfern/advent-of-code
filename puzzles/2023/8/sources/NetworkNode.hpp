#pragma once

#include "Instruction.hpp"
#include <array>
#include <string>

namespace aoc_2023_8 {

using NodeId = std::string;

class NetworkNode {
public:
    NetworkNode(NodeId leftNode, NodeId rightNode);

    [[nodiscard]] NodeId navigate(Instruction instruction) const noexcept;

private:
    std::array<NodeId, 2> mNextNodes;
};

} // namespace aoc_2023_8
