#include "NodeMap.hpp"
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2022_12 {

NodeMap::NodeMap(std::vector<std::vector<Node>>&& nodes)
    : mNodes{ std::move(nodes) }
{
}

bool NodeMap::canMove(const Node& node, const Direction2D direction)
{
    const auto movement{ direction.toVector2D() };
    Point2D newPosition{ node.getPosition() + movement };
    newPosition.move(direction);
    const auto newNode{ getNodeFromPosition(newPosition) };
    return node <= newNode;
}

std::pair<std::size_t, std::size_t> NodeMap::size() const
{
    return std::make_pair(mNodes.size(), mNodes[0].size());
}
const Node& NodeMap::getNodeFromPosition(const Point2D& position) const
{
    const auto positionX{ static_cast<size_t>(position.getX()) };
    const auto positionY{ static_cast<size_t>(position.getY()) };
    return mNodes.at(positionX).at(positionY);
}

} // namespace aoc_2022_12