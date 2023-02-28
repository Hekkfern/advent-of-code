#include "PositionMap.hpp"

#include <range/v3/all.hpp>
#include <utils/geometry2d/Direction2D.hpp>

namespace aoc_2022_12 {

PositionMap::PositionMap(
    std::unordered_map<Point2D, Position>&& positions,
    size_t width,
    size_t height)
    : mPositions{ std::move(positions) }
    , mWidth{ width }
    , mHeight{ height }
{
    lookForExtremes();
    initializeCosts();
}

PositionMap::PositionMap(
    std::unordered_map<Point2D, Position>&& positions,
    size_t width,
    size_t height,
    const Position& origin,
    const Position& destination)
    : mPositions{ std::move(positions) }
    , mWidth{ width }
    , mHeight{ height }
    , mOrigin{ &origin }
    , mDestination{ &destination }
{
    initializeCosts();
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
    return std::make_pair(mWidth, mHeight);
}

const Position& PositionMap::getPositionFromCoordinates(
    const Point2D& coords) const
{
    return mPositions.at(coords);
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
    bool originFound{ false };
    bool destFound{ false };
    for (const auto& [point, item] : mPositions) {
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

const Position& PositionMap::getOrigin() const { return *mOrigin; }

const Position& PositionMap::getDestination() const { return *mDestination; }

void PositionMap::initializeCosts()
{
    mCosts.reserve(size().first * size().second);
    for (const auto& [point, item] : mPositions) {
        mCosts.emplace(point, UINT32_MAX);
    }
}

void PositionMap::setCost(const Position& position, uint32_t newCost)
{
    mCosts.at(position.getPoint()) = newCost;
}

uint32_t PositionMap::getCost(const Position& position)
{
    return mCosts.at(position.getPoint());
}

const Position& PositionMap::move(
    const Position& position,
    const Direction2D direction) const
{
    auto coords{ position.getPoint() + direction };
    return getPositionFromCoordinates(coords);
}

} // namespace aoc_2022_12
