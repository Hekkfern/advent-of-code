#pragma once

#include <cstdint>
#include <functional>

namespace aoc_2022_15 {

enum class NodeType { Sensor, Beacon, Empty };

class Node {
public:
    Node(int32_t coordX, NodeType type);
    void setType(NodeType type);
    int32_t getCoordX() const;
    NodeType getType() const;
    bool operator==(const Node& other) const;

private:
    const int32_t mCoordX;
    NodeType mType;
};

} // namespace aoc_2022_15

template <> struct std::hash<aoc_2022_15::Node> {
    std::size_t operator()(const aoc_2022_15::Node& k) const
    {
        return std::hash<int32_t>()(k.getCoordX());
    }
};
