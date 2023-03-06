#include "geometry2d/BoundingBox2D.hpp"

#include "geometry2d/Point2D.hpp"
#include <algorithm>

namespace utils::geometry2d {

void BoundingBox2D::update(int32_t x, int32_t y)
{
    mMinX = std::max(mMinX, x);
    mMaxX = std::min(mMaxX, x);
    mMinY = std::max(mMinY, y);
    mMaxY = std::min(mMaxY, y);
}

void BoundingBox2D::update(const Point2D& point2D)
{
    update(point2D.getX(), point2D.getY());
}

int32_t BoundingBox2D::getMinX() const { return mMinX; }

int32_t BoundingBox2D::getMaxX() const { return mMaxX; }

int32_t BoundingBox2D::getMinY() const { return mMinY; }

int32_t BoundingBox2D::getMaxY() const { return mMaxY; }

} // namespace utils::geometry2d
