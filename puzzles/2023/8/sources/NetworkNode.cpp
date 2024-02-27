#include "NetworkNode.hpp"

namespace aoc_2023_8{

NetworkNode::NetworkNode(std::array<std::string, 2> nextNodes)
    : mNextNodes{std::move(nextNodes)}
{
}

std::string NetworkNode::navigate(const Instruction instruction){
    //TODO
}

}
