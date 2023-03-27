#include "geometry2d/Point2D.hpp"

#include "geometry2d/Direction2D.hpp"
#include "geometry2d/Vector2D.hpp"
#include <iostream>

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

void Point2D::move(Direction2D direction2D) { move(direction2D.toVector2D()); }

void Point2D::move(const Vector2D& vector2D)
{
    mX += vector2D.getX();
    mY += vector2D.getY();
}

std::pair<int32_t, int32_t> Point2D::getCoordinates() const
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

Point2D Point2D::move(const Point2D& point2d, const Vector2D& vector2d)
{
    return Point2D{ point2d.mX + vector2d.getX(),
                    point2d.mY + vector2d.getY() };
}

Point2D Point2D::move(const Point2D& point2d, const Direction2D& direction2D)
{
    return Point2D::move(point2d, direction2D.toVector2D());
}

Point2D operator+(const Point2D& point2d, const Vector2D& vector2d)
{
    return Point2D::move(point2d, vector2d);
}

Point2D operator+(const Vector2D& vector2d, const Point2D& point2d)
{
    return point2d + vector2d;
}

Point2D operator+(const Point2D& point2d, const Direction2D& direction2D)
{
    return Point2D::move(point2d, direction2D);
}

Point2D operator+(const Direction2D& direction2D, const Point2D& point2d)
{
    return point2d + direction2D;
}

std::ostream& operator<<(std::ostream& os, const Point2D& point2d)
{
    os << '(' << point2d.mX << ',' << point2d.mY << ')';
    return os;
}

} // namespace utils::geometry2d
