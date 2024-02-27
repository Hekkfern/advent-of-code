#include "NetworkNode.hpp"

#include <cassert>

namespace aoc_2023_8 {

NetworkNode::NetworkNode(NodeId leftNode, NodeId rightNode)
    : mNextNodes{std::array{std::move(leftNode), std::move(rightNode)}}
{
}

NodeId NetworkNode::navigate(Instruction const instruction)
{
    switch (instruction) {
    case Instruction::Left:
        return mNextNodes[0];
    case Instruction::Right:
        return mNextNodes[1];
    default:
        assert("Wrong instruction");
        return {};
    }
}

} // namespace aoc_2023_8
