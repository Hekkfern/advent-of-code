#pragma once

#include "Position.hpp"
#include <unordered_map>

namespace aoc_2022_12 {

enum class ClimbingDirection { Up, Down };

class PositionMap {
public:
    PositionMap(
        std::unordered_map<Point2D<int32_t>, Position>&& positions,
        size_t width,
        size_t height);
    PositionMap(
        std::unordered_map<Point2D<int32_t>, Position>&& positions,
        size_t width,
        size_t height,
        Position const& origin,
        Position const& destination);
    bool canMove(
        Position const& position,
        Direction2D const direction,
        ClimbingDirection climbingDirection) const;
    std::pair<std::size_t, std::size_t> size() const;
    Position const& getOrigin() const;
    Position const& getDestination() const;
    void setCost(Position const& position, uint32_t newCost);
    uint32_t getCost(Position const& position);
    Position const&
    move(Position const& position, Direction2D const direction) const;

private:
    Position const&
    getPositionFromCoordinates(Point2D<int32_t> const& coords) const;
    bool isMovementOutOfBounds(
        Position const& position, Direction2D const direction) const;
    void lookForExtremes();
    void initializeCosts();

    std::unordered_map<Point2D<int32_t>, Position> const mPositions;
    std::unordered_map<Point2D<int32_t>, uint32_t> mCosts;
    size_t const mWidth;
    size_t const mHeight;
    Position const* mOrigin;
    Position const* mDestination;
};

} // namespace aoc_2022_12
