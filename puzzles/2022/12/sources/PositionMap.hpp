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
    bool canMove(const Position& position, const Direction2D direction) const;
    std::pair<std::size_t, std::size_t> size() const;
    const Position& getOrigin() const;
    const Position& getDestination() const;
    void setCost(const Position& position, uint32_t newCost);
    uint32_t getCost(const Position& position);

private:
    const Position& getPositionFromCoordinates(const Point2D& coords) const;
    bool isMovementOutOfBounds(
        const Position& position,
        const Direction2D direction) const;
    void lookForExtremes();
    void initializeCosts();

    const std::vector<std::vector<Position>> mPositions;
    std::vector<std::vector<uint32_t>> mCosts;
    const Position* mOrigin;
    const Position* mDestination;
};

} // namespace aoc_2022_12
