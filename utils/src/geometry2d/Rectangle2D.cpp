#include "geometry2d/Rectangle2D.hpp"

#include <range/v3/all.hpp>
#include <vector>

namespace utils::geometry2d {

Rectangle2D::Rectangle2D(
    const utils::geometry2d::Point2D& bottomLeft,
    size_t width,
    size_t height)
    : mVertexes{ { bottomLeft,
                   bottomLeft + Vector2D{ static_cast<int32_t>(width), 0 },
                   bottomLeft
                       + Vector2D{ static_cast<int32_t>(width),
                                   static_cast<int32_t>(height) },
                   bottomLeft + Vector2D{ 0, static_cast<int32_t>(height) } } }
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

uint32_t Rectangle2D::area() const
{
    return static_cast<uint32_t>(mWidth * mHeight);
}

bool Rectangle2D::isOutside(const Point2D& point) const
{
    return !isInside(point);
}

bool Rectangle2D::isInPerimeter(const Point2D& point) const
{
    const Vector2D v1{ getBottomLeftPoint(), point };
    const Vector2D v2{ getTopRightPoint(), point };
    return v1.isVertical() || v1.isHorizontal() || v2.isVertical()
        || v2.isHorizontal();
}

bool Rectangle2D::isInside(const Point2D& point) const
{
    const auto& bottomLeft{ getBottomLeftPoint() };
    const auto& topRight{ getTopRightPoint() };
    return (bottomLeft.getX() <= point.getX())
        && (point.getX() <= topRight.getX())
        && (bottomLeft.getY() <= point.getY())
        && (point.getY() <= topRight.getY());
}

const Point2D& Rectangle2D::getBottomLeftPoint() const
{
    return mVertexes.at(0);
}

const Point2D& Rectangle2D::getTopRightPoint() const { return mVertexes.at(2); }

std::vector<Point2D> Rectangle2D::getVertexes() const
{
    return { std::begin(mVertexes), std::end(mVertexes) };
}

} // namespace utils::geometry2d
