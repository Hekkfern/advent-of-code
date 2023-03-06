#include "SandMap.hpp"

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

bool SandMap::addSandGrain()
{
    // todo
}

} // namespace aoc_2022_14