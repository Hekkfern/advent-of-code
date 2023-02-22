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

Point2D::Point2D(const std::pair<int32_t, int32_t>& coords)
    : mX{ coords.first }
    , mY{ coords.second }
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

bool Point2D::operator==(const Point2D& other) const
{
    return (mX == other.mX) && (mY == other.mY);
}

Point2D Point2D::operator+(const Point2D& other) const
{
    return { mX + other.mX, mY + other.mY };
}

Point2D Point2D::operator-(const Point2D& other) const
{
    return *this + (-other);
}

Point2D Point2D::operator-() const { return { -mX, -mY }; }

Point2D operator+(const Point2D& point2d, const Vector2D& vector2d)
{
    Point2D newPoint{ point2d };
    newPoint.move(vector2d);
    return newPoint;
}

Point2D operator+(const Vector2D& vector2d, const Point2D& point2d)
{
    return point2d + vector2d;
}

} // namespace utils::geometry2d
