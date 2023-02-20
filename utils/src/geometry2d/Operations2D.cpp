#include "geometry2d/Operations2D.hpp"

#include "geometry2d/Point2D.hpp"
#include "geometry2d/Vector2D.hpp"

namespace utils::geometry2d {

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

Vector2D operator*(const Vector2D& vector2D, const int32_t n)
{
    return Vector2D{ n * vector2D.getX(), n * vector2D.getY() };
}

Vector2D operator*(const int32_t n, const Vector2D& vector2D)
{
    return vector2D * n;
}

} // namespace utils::geometry2d