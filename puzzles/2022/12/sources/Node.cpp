#include "Node.hpp"

namespace aoc_2022_12 {

Node::Node(Point2D&& pos, const Height height, bool isStartingPoint)
    : mPosition2D{ std::move(pos) }
    , mIsStartingPoint{ isStartingPoint }
    , mHeight{ height }
{
}

} // namespace aoc_2022_12