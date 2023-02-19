#include "geometry2d/Point2D.hpp"

#include "geometry2d/Direction.hpp"
#include "geometry2d/Vector2D.hpp"

namespace utils::geometry2d {

Point2D::Point2D()
    : mX{ 0 }
    , mY{ 0 }
{
}

Point2D::Point2D(int32_t x, int32_t y)
    : mX{ x }
    , mY{ y }
{
}

void Point2D::move(Direction direction)
{
    switch (direction) {
    case Direction::Left:
    case Direction::DownLeft:
    case Direction::UpLeft:
        --mX;
        break;
    case Direction::Right:
    case Direction::UpRight:
    case Direction::DownRight:
        ++mX;
        break;
    default:
        /* NO STATEMENTS */
        break;
    }
    switch (direction) {
    case Direction::Down:
    case Direction::DownRight:
    case Direction::DownLeft:
        --mY;
        break;
    case Direction::Up:
    case Direction::UpRight:
    case Direction::UpLeft:
        ++mY;
        break;
    default:
        /* NO STATEMENTS */
        break;
    }
}

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
