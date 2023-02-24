#include "PositionMap.hpp"
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2022_12 {

PositionMap::PositionMap(std::vector<std::vector<Position>>&& nodes)
    : mPositions{ std::move(nodes) }
{
    lookForExtremes();
}

PositionMap::PositionMap(
    std::vector<std::vector<Position>>&& nodes,
    const Position& origin,
    const Position& destination)
    : mPositions{ std::move(nodes) }
    , mOrigin{ &origin }
    , mDestination{ &destination }
{
}

bool PositionMap::canMove(const Position& position, const Direction2D direction)
    const
{
    // check boundaries of the map
    if (isMovementOutOfBounds(position, direction)) {
        return false;
    }
    // check height gap
    const auto movement{ direction.toVector2D() };
    Point2D newPoint{ position.getPoint() + movement };
    newPoint.move(direction);
    const auto newNode{ getPositionFromCoordinates(newPoint) };
    return position <= newNode;
}

std::pair<std::size_t, std::size_t> PositionMap::size() const
{
    return std::make_pair(mPositions.size(), mPositions[0].size());
}

const Position& PositionMap::getPositionFromCoordinates(
    const Point2D& coords) const
{
    const auto positionX{ static_cast<size_t>(coords.getX()) };
    const auto positionY{ static_cast<size_t>(coords.getY()) };
    return mPositions.at(positionX).at(positionY);
}
bool PositionMap::isMovementOutOfBounds(
    const Position& position,
    const Direction2D direction) const
{
    const auto [coordX, coordY]{ position.getCoordinates() };
    const auto [sizeX, sizeY]{ size() };
    if (coordX == 0 && direction == Direction2D::Left) {
        return true;
    }
    if (coordY == 0 && direction == Direction2D::Down) {
        return true;
    }
    if (coordY == (sizeY - 1U) && direction == Direction2D::Up) {
        return true;
    }
    if (coordX == (sizeX - 1U) && direction == Direction2D::Right) {
        return true;
    }
    return false;
}

void PositionMap::lookForExtremes()
{
    bool originFound = false;
    bool destFound = false;
    for (const auto& row : mPositions) {
        for (const auto& item : row) {
            if (item.getType() == PositionType::Origin) {
                mOrigin = &item;
                originFound = true;
            }
            if (item.getType() == PositionType::Destination) {
                mDestination = &item;
                destFound = true;
            }
            if (originFound && destFound) {
                return;
            }
        }
    }
}

const Position& PositionMap::getOrigin() const { return *mOrigin; }

const Position& PositionMap::getDestination() const { return *mDestination; }

} // namespace aoc_2022_12