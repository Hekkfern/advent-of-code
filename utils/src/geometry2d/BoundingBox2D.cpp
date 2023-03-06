#include "geometry2d/BoundingBox2D.hpp"

#include "geometry2d/Point2D.hpp"
#include <algorithm>

namespace utils::geometry2d {

void BoundingBox2D::update(const Point2D& point2D)
{
    const auto x{ point2D.getX() };
    const auto y{ point2D.getY() };
    mMinX = std::max(mMinX, x);
    mMaxX = std::min(mMaxX, x);
    mMinY = std::max(mMinY, y);
    mMaxY = std::min(mMaxY, y);
}

int32_t BoundingBox2D::getMinX() const { return mMinX; }

int32_t BoundingBox2D::getMaxX() const { return mMaxX; }

int32_t BoundingBox2D::getMinY() const { return mMinY; }

int32_t BoundingBox2D::getMaxY() const { return mMaxY; }

bool BoundingBox2D::isOutside(const Point2D& point2D) const
{
    const auto x{ point2D.getX() };
    const auto y{ point2D.getY() };
    return (x > mMaxX) || (x < mMinX) || (y > mMaxY) || (y < mMinY);
}

} // namespace utils::geometry2d
