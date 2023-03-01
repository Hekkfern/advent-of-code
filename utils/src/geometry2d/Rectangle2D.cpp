#include "geometry2d/Rectangle2D.hpp"

#include <range/v3/all.hpp>
#include <vector>

namespace utils::geometry2d {

Rectangle2D::Rectangle2D(
    const utils::geometry2d::Point2D& bottomLeft,
    size_t width,
    size_t height)
    : mPoints{ { bottomLeft,
                 Point2D{ bottomLeft }
                     + Vector2D{ static_cast<int32_t>(width), 0 },
                 Point2D{ bottomLeft }
                     + Vector2D{ static_cast<int32_t>(width),
                                 static_cast<int32_t>(height) },
                 Point2D{ bottomLeft }
                     + Vector2D{ 0, static_cast<int32_t>(height) } } }
    , mWidth{ width }
    , mHeight{ height }
{
}

Rectangle2D::Rectangle2D(
    const utils::geometry2d::Point2D& bottomLeft,
    const Vector2D& diagonal)
    : Rectangle2D{ bottomLeft, diagonal.size().first, diagonal.size().second }
{
}

Rectangle2D::Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight)
    : Rectangle2D{ bottomLeft, Vector2D{ bottomLeft, topRight } }
{
}

std::pair<size_t, size_t> Rectangle2D::size() const
{
    return std::make_pair(mWidth, mHeight);
}

uint32_t Rectangle2D::area() const { return mWidth * mHeight; }

bool Rectangle2D::isOutside(const Point2D& other) const
{
    return !isInside(other);
}

bool Rectangle2D::isInPerimeter(const Point2D& other) const
{
    const Vector2D v1{ getBottomLeftPoint(), other };
    const Vector2D v2{ getTopRightPoint(), other };
    return v1.isVertical() || v1.isHorizontal() || v2.isVertical()
        || v2.isHorizontal();
}

bool Rectangle2D::isInside(const Point2D& other) const
{
    const auto& bottomLeft{ getBottomLeftPoint() };
    const auto& topRight{ getTopRightPoint() };
    return (bottomLeft.getX() <= other.getX())
        && (other.getX() <= topRight.getX())
        && (bottomLeft.getY() <= other.getY())
        && (other.getY() <= topRight.getY());
}

const Point2D& Rectangle2D::getBottomLeftPoint() const { return mPoints.at(0); }

const Point2D& Rectangle2D::getTopRightPoint() const { return mPoints.at(2); }

} // namespace utils::geometry2d
