#include "geometry2d/BoundingBox2D.hpp"

#include "geometry2d/Direction2D.hpp"
#include "geometry2d/Point2D.hpp"
#include <algorithm>

namespace utils::geometry2d {

void BoundingBox2D::update(const Point2D& point2D)
{
    const auto x{ point2D.getX() };
    const auto y{ point2D.getY() };
    mMinX = std::min(mMinX, x);
    mMaxX = std::max(mMaxX, x);
    mMinY = std::min(mMinY, y);
    mMaxY = std::max(mMaxY, y);
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

bool BoundingBox2D::isOutside(
    const Point2D& point2D,
    const Direction2D direction2D) const
{
    const auto x{ point2D.getX() };
    const auto y{ point2D.getY() };
    switch (direction2D) {
    case Direction2D::Up:
        return y > mMaxY;
    case Direction2D::Left:
        return x < mMinX;
    case Direction2D::Down:
        return y < mMinY;
    case Direction2D::Right:
        return x > mMaxX;
    default:
        return false;
    }
}

} // namespace utils::geometry2d
