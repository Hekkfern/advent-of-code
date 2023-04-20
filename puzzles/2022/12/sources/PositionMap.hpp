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
        const Position& origin,
        const Position& destination);
    bool canMove(
        const Position& position,
        const Direction2D direction,
        ClimbingDirection climbingDirection) const;
    std::pair<std::size_t, std::size_t> size() const;
    const Position& getOrigin() const;
    const Position& getDestination() const;
    void setCost(const Position& position, uint32_t newCost);
    uint32_t getCost(const Position& position);
    const Position&
    move(const Position& position, const Direction2D direction) const;

private:
    const Position&
    getPositionFromCoordinates(const Point2D<int32_t>& coords) const;
    bool isMovementOutOfBounds(
        const Position& position, const Direction2D direction) const;
    void lookForExtremes();
    void initializeCosts();

    const std::unordered_map<Point2D<int32_t>, Position> mPositions;
    std::unordered_map<Point2D<int32_t>, uint32_t> mCosts;
    const size_t mWidth;
    const size_t mHeight;
    const Position* mOrigin;
    const Position* mDestination;
};

} // namespace aoc_2022_12
