#include "PositionMap.hpp"

#include <range/v3/all.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Operations2D.hpp>

namespace aoc_2022_12 {

PositionMap::PositionMap(
    std::unordered_map<Point2D<int32_t>, Position>&& positions,
    size_t width,
    size_t height)
    : mPositions{std::move(positions)}
    , mWidth{width}
    , mHeight{height}
{
    lookForExtremes();
    initializeCosts();
}

PositionMap::PositionMap(
    std::unordered_map<Point2D<int32_t>, Position>&& positions,
    size_t width,
    size_t height,
    Position const& origin,
    Position const& destination)
    : mPositions{std::move(positions)}
    , mWidth{width}
    , mHeight{height}
    , mOrigin{&origin}
    , mDestination{&destination}
{
    initializeCosts();
}

bool PositionMap::canMove(
    Position const& position,
    Direction2D const direction,
    ClimbingDirection climbingDirection) const
{
    // check boundaries of the map
    if (isMovementOutOfBounds(position, direction)) {
        return false;
    }
    // check height gap
    Point2D<int32_t> const newPoint{position.getPoint() + direction};
    auto const nextPosition{getPositionFromCoordinates(newPoint)};
    if (climbingDirection == ClimbingDirection::Down) {
        // valid: higher, equal or 1 unit lower
        return nextPosition.getHeight() >= (position.getHeight() - 1U);
    } else {
        // valid: lower, equal or 1 unit higher.
        return nextPosition.getHeight() <= (position.getHeight() + 1U);
    }
}

/**
 * @brief Gets the size of the map.
 *
 * @return Returns a pair where the first item is the Width (number of columns
 * or coordinate X) and the second item is the Height (number of rows or
 * coordinate Y).
 */
std::pair<std::size_t, std::size_t> PositionMap::size() const
{
    return std::make_pair(mWidth, mHeight);
}

Position const&
PositionMap::getPositionFromCoordinates(Point2D<int32_t> const& coords) const
{
    return mPositions.at(coords);
}

bool PositionMap::isMovementOutOfBounds(
    Position const& position, Direction2D const direction) const
{
    auto const [coordX, coordY]{position.getCoordinates()};
    auto const [sizeX, sizeY]{size()};
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
    bool originFound{false};
    bool destFound{false};
    for (auto const& [point, item] : mPositions) {
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

Position const& PositionMap::getOrigin() const { return *mOrigin; }

Position const& PositionMap::getDestination() const { return *mDestination; }

void PositionMap::initializeCosts()
{
    mCosts.reserve(size().first * size().second);
    for (auto const& [point, item] : mPositions) {
        mCosts.emplace(point, std::numeric_limits<uint32_t>::max());
    }
}

void PositionMap::setCost(Position const& position, uint32_t newCost)
{
    mCosts.at(position.getPoint()) = newCost;
}

uint32_t PositionMap::getCost(Position const& position)
{
    return mCosts.at(position.getPoint());
}

Position const&
PositionMap::move(Position const& position, Direction2D const direction) const
{
    auto coords{position.getPoint() + direction};
    return getPositionFromCoordinates(coords);
}

} // namespace aoc_2022_12
