#include "Node.hpp"

namespace aoc_2022_12 {

Node::Node(Point2D&& pos, const Height height, bool isStartingPoint)
    : mPosition2D{ std::move(pos) }
    , mIsStartingPoint{ isStartingPoint }
    , mHeight{ height }
{
}

const Point2D& Node::getPosition() const { return mPosition2D; }

Height Node::getHeight() const { return mHeight; }

bool Node::isStartingPoint() const { return mIsStartingPoint; }

bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.mHeight == rhs.mHeight;
}

bool operator!=(const Node& lhs, const Node& rhs) { return !(lhs == rhs); }

bool operator>(const Node& lhs, const Node& rhs)
{
    return lhs.mHeight > rhs.mHeight;
}

bool operator<(const Node& lhs, const Node& rhs)
{
    return !(lhs > rhs) && !(lhs == rhs);
}

} // namespace aoc_2022_12