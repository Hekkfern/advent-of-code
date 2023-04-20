#include "SandMap.hpp"

#include <cassert>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2022_14 {

void SandMap::addRockLine(
    const Point2D<int32_t>& start, const Point2D<int32_t>& end)
{
    Vector2D vector2D{start, end};
    vector2D.normalize();
    Point2D<int32_t> nextPoint{start};
    do {
        // add rock
        mRocks.emplace(nextPoint);
        // update bounding box
        mBoundingBox.update(nextPoint);
        // update assumed floor
        mAssumedFloorHeight = std::max(
            mAssumedFloorHeight, nextPoint.getY() + 2);
        // next
        nextPoint = nextPoint + vector2D;
    } while (nextPoint != end);
    // add final rock in the line
    mRocks.emplace(nextPoint);
    mBoundingBox.update(nextPoint);
}

uint32_t SandMap::getNumberOfSandGrains() const
{
    return static_cast<uint32_t>(mSand.size());
}

static const Point2D<int32_t> SandOrigin{500, 0};
constexpr Direction2D FallingDirection{Direction2D::Up};
constexpr Direction2D SlidingLeftDirection{Direction2D::UpLeft};
constexpr Direction2D SlidingRightDirection{Direction2D::UpRight};

std::optional<Point2D<int32_t>>
SandMap::sandGoDown(const Point2D<int32_t>& position)
{
    Point2D<int32_t> nextPosition{position + FallingDirection};
    if (mRocks.contains(nextPosition) || mSand.contains(nextPosition)) {
        return std::nullopt;
    }
    if (mInfiniteFloorEnabled && nextPosition.getY() >= mAssumedFloorHeight) {
        return std::nullopt;
    }
    return std::make_optional(nextPosition);
}

std::optional<Point2D<int32_t>> SandMap::sandSlide(
    const Point2D<int32_t>& position, const Direction2D& direction2D)
{
    assert(
        (direction2D == SlidingLeftDirection)
        || (direction2D == SlidingRightDirection));
    Point2D<int32_t> nextPosition{position + direction2D};
    if (mRocks.contains(nextPosition) || mSand.contains(nextPosition)) {
        return std::nullopt;
    }
    if (mInfiniteFloorEnabled && nextPosition.getY() >= mAssumedFloorHeight) {
        return std::nullopt;
    }
    return std::make_optional(nextPosition);
}

bool SandMap::addSandGrainInConstrainedSpace()
{
    Point2D<int32_t> grainPosition{SandOrigin};
    while (true) {
        std::optional<Point2D<int32_t>> candidatePosition;
        // go down
        if (candidatePosition = sandGoDown(grainPosition); candidatePosition) {
            if (isOutside(*candidatePosition)) {
                return false;
            }
            grainPosition = *candidatePosition;
            continue;
        }
        // try to slide both sides
        if (candidatePosition = sandSlide(grainPosition, SlidingLeftDirection);
            candidatePosition) {
            if (isOutside(*candidatePosition)) {
                return false;
            }
            grainPosition = *candidatePosition;
            continue;
        }
        if (candidatePosition = sandSlide(grainPosition, SlidingRightDirection);
            candidatePosition) {
            if (isOutside(*candidatePosition)) {
                return false;
            }
            grainPosition = *candidatePosition;
            continue;
        }
        // the sand grain is steady
        mSand.emplace(grainPosition);
        return true;
    }
}

bool SandMap::isOutside(const Point2D<int32_t>& position) const
{
    return mBoundingBox.isOutside(position, Direction2D::Left)
        || mBoundingBox.isOutside(position, Direction2D::Up)
        || mBoundingBox.isOutside(position, Direction2D::Right);
}

bool SandMap::addSandGrainInInfiniteSpace()
{
    Point2D<int32_t> grainPosition{SandOrigin};
    while (true) {
        std::optional<Point2D<int32_t>> candidatePosition;
        // go down
        if (candidatePosition = sandGoDown(grainPosition); candidatePosition) {
            grainPosition = *candidatePosition;
            continue;
        }
        // try to slide both sides
        if (candidatePosition = sandSlide(grainPosition, SlidingLeftDirection);
            candidatePosition) {
            grainPosition = *candidatePosition;
            continue;
        }
        if (candidatePosition = sandSlide(grainPosition, SlidingRightDirection);
            candidatePosition) {
            grainPosition = *candidatePosition;
            continue;
        }
        // the sand grain is steady
        mSand.emplace(grainPosition);
        return grainPosition != SandOrigin;
    }
}

void SandMap::enableInfiniteFloor() { mInfiniteFloorEnabled = true; }

} // namespace aoc_2022_14