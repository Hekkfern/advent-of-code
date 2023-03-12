#include "Node.hpp"

namespace aoc_2022_15 {

bool Node::operator==(const Node& other) const
{
    return mCoordX == other.mCoordX;
}

int32_t Node::getCoordX() const { return mCoordX; }

void Node::setType(NodeType type) { mType = type; }

Node::Node(int32_t coordX, NodeType type)
    : mCoordX{ coordX }
    , mType{ type }
{
}

NodeType Node::getType() const { return mType; }

} // namespace aoc_2022_15
