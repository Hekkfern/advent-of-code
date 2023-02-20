#pragma once

#include "Node.hpp"
#include <vector>

namespace aoc_2022_12 {

class NodeMap {
public:
    NodeMap(std::vector<std::vector<Node>>&& nodes);
    bool canMove(const Node& node, const Direction2D direction);
    std::pair<std::size_t, std::size_t> size() const;

private:
    const Node& getNodeFromPosition(const Point2D& position) const;

    const std::vector<std::vector<Node>> mNodes;
};

} // namespace aoc_2022_12
