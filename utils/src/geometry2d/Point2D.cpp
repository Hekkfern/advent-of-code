#include "geometry2d/Point2D.hpp"

#include "geometry2d/Direction2D.hpp"
#include "geometry2d/Vector2D.hpp"

namespace utils::geometry2d {

Point2D::Point2D() { }

Point2D::Point2D(int32_t x, int32_t y)
    : mX{ x }
    , mY{ y }
{
}

void Point2D::move(Direction2D direction) { move(direction.toVector2D()); }

void Point2D::move(const Vector2D& vector)
{
    mX += vector.getX();
    mY += vector.getY();
}

std::pair<int32_t, int32_t> Point2D::get() const
{
    return std::make_pair(mX, mY);
}

int32_t Point2D::getX() const { return mX; }

int32_t Point2D::getY() const { return mY; }

bool operator==(const Point2D& lhs, const Point2D& rhs)
{
    return (lhs.mX == rhs.mX) && (lhs.mY == rhs.mY);
}

bool operator!=(const Point2D& lhs, const Point2D& rhs)
{
    return !(lhs == rhs);
}

} // namespace utils::geometry2d
