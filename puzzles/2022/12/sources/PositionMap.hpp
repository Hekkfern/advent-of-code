#pragma once

#include "Position.hpp"
#include <vector>

namespace aoc_2022_12 {

class PositionMap {
public:
    PositionMap(std::vector<std::vector<Position>>&& nodes);
    PositionMap(
        std::vector<std::vector<Position>>&& nodes,
        const Position& origin,
        const Position& destination);
    bool canMove(const Position& position, const Direction2D direction);
    std::pair<std::size_t, std::size_t> size() const;

private:
    const Position& getPositionFromCoordinates(const Point2D& coords) const;
    bool isMovementOutOfBounds(
        const Position& position,
        const Direction2D direction) const;
    void lookForExtremes();

    const std::vector<std::vector<Position>> mPositions;
    const Position* mOrigin;
    const Position* mDestination;
};

} // namespace aoc_2022_12
