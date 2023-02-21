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

Vector2D::Vector2D(const std::pair<int32_t, int32_t>& coords)
    : mX{ coords.first }
    , mY{ coords.second }
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

bool Vector2D::operator==(const Vector2D& other) const
{
    return (mX == other.mX) && (mY == other.mY);
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return { mX + other.mX, mY + other.mY };
}

Vector2D Vector2D::operator-() const { return { -mX, -mY }; }

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return *this + (-other);
}

void Vector2D::normalize()
{
    // saturate X
    mX = std::clamp(mX, -1, 1);
    // saturate Y
    mY = std::clamp(mY, -1, 1);
}

bool Vector2D::isZero() const { return mX == 0 && mY == 0; }

Vector2D Vector2D::getNormalized() const
{
    Vector2D vector2D(*this);
    vector2D.normalize();
    return vector2D;
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
