#include "Position2D.h"

#include "Direction.h"
#include "Vector2D.h"
#include <algorithm>

namespace aoc_2022_9 {

void Position2D::move(Direction direction)
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

void Position2D::move(const Vector2D& vector)
{
    mX += vector.getX();
    mY += vector.getY();
}

std::pair<int32_t, int32_t> Position2D::get() const
{
    return std::make_pair(mX, mY);
}

int32_t Position2D::getX() const { return mX; }

int32_t Position2D::getY() const { return mY; }

bool operator==(const Position2D& lhs, const Position2D& rhs)
{
    return (lhs.mX == rhs.mX) && (lhs.mY == rhs.mY);
}

bool operator!=(const Position2D& lhs, const Position2D& rhs)
{
    return !(lhs == rhs);
}

} // namespace aoc_2022_9
