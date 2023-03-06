#include "SandMap.hpp"

#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2022_14 {

void SandMap::addRockLine(const Point2D& start, const Point2D& end)
{
    Vector2D vector2D{ start, end };
    vector2D.normalize();
    Point2D nextPoint{ start };
    do {
        // add rock
        mRocks.emplace(nextPoint);
        // update bounding box
        mBoundingBox.update(nextPoint);
        // next
        nextPoint.move(vector2D);
    } while (nextPoint != end);
}

uint32_t SandMap::getNumberOfSandGrains() const { return mSand.size(); }

static const Point2D SandOrigin{ 500, 0 };
constexpr Direction2D FallingDirection{ Direction2D::Up };
constexpr Direction2D SlidingLeftDirection{ Direction2D::UpLeft };
constexpr Direction2D SlidingRightDirection{ Direction2D::UpRight };

std::optional<Point2D> SandMap::sandGoDown(const Point2D& position)
{
    Point2D nextPosition{ Point2D::move(position, FallingDirection) };
    if (mRocks.contains(nextPosition) || mSand.contains(nextPosition)) {
        return std::nullopt;
    }
    return std::make_optional(nextPosition);
}

std::optional<Point2D> SandMap::sandSlide(
    const Point2D& position,
    const Direction2D& direction2D)
{
    assert(
        (direction2D == SlidingLeftDirection)
        || (direction2D == SlidingRightDirection));
    Point2D nextPosition{ Point2D::move(position, direction2D) };
    if (mRocks.contains(nextPosition) || mSand.contains(nextPosition)) {
        return std::nullopt;
    }
    return std::make_optional(nextPosition);
}

bool SandMap::addSandGrain()
{
    Point2D grainPosition{ SandOrigin };
    while (true) {
        // go down
        while (true) {
            auto nextPosition{ sandGoDown(grainPosition) };
            if (!nextPosition) {
                break;
            }
            if (mBoundingBox.isOutside(*nextPosition)) {
                return false;
            }
            grainPosition = *nextPosition;
        }
        // try to slide both sides
        if (auto leftPosition{ sandSlide(grainPosition, SlidingLeftDirection) };
            leftPosition) {
            if (mBoundingBox.isOutside(*leftPosition)) {
                return false;
            }
            grainPosition = *leftPosition;
            continue;
        }
        if (auto rightPosition{
                sandSlide(grainPosition, SlidingRightDirection) };
            rightPosition) {
            if (mBoundingBox.isOutside(*rightPosition)) {
                return false;
            }
            grainPosition = *rightPosition;
            continue;
        }
        // the sand grain is steady
        return true;
    }
}

} // namespace aoc_2022_14