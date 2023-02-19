#include "geometry2d/Vector2D.hpp"

#include "geometry2d/Point2D.hpp"
#include <algorithm>
#include <cstdlib>

namespace utils::geometry2d {

Vector2D::Vector2D(int32_t x, int32_t y)
    : mX{ x }
    , mY{ y }
{
}

Vector2D::Vector2D(const Point2D& origin, const Point2D& destination)
    : mX{ destination.getX() - origin.getX() }
    , mY{ destination.getY() - origin.getY() }
{
}

std::pair<int32_t, int32_t> Vector2D::get() const
{
    return std::make_pair(mX, mY);
}

int32_t Vector2D::getX() const { return mX; }

int32_t Vector2D::getY() const { return mY; }

uint32_t Vector2D::distance() const
{
    return static_cast<uint32_t>(std::max(std::abs(mX), std::abs(mY)));
}

} // namespace aoc_2022_9
