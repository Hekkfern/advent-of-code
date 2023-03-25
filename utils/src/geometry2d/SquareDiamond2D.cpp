#include "geometry2d/SquareDiamond2D.hpp"

#include "geometry2d/Vector2D.hpp"

namespace utils::geometry2d {

SquareDiamond2D::SquareDiamond2D(
    const Point2D& centerPoint,
    const Point2D& perimeterPoint)
    : SquareDiamond2D{ centerPoint,
                       Vector2D{ centerPoint, perimeterPoint }.distance() }
{
}

SquareDiamond2D::SquareDiamond2D(
    const Point2D& centerPoint,
    const uint32_t distance)
    : mCenter{ centerPoint }
    , mDistance{ distance }
    , mVertexes{ centerPoint + Vector2D{ 0, static_cast<int32_t>(mDistance) },
                 centerPoint + Vector2D{ static_cast<int32_t>(mDistance), 0 },
                 centerPoint + Vector2D{ 0, -static_cast<int32_t>(mDistance) },
                 centerPoint + Vector2D{ -static_cast<int32_t>(mDistance), 0 } }
{
}

uint32_t SquareDiamond2D::getDistance() const { return mDistance; }

const Point2D& SquareDiamond2D::getCenter() const { return mCenter; }

std::optional<Point2D> SquareDiamond2D::stepAroundPerimeter() const noexcept
{
    const auto& [centerCoordX, centerCoordY] = mCenter.getCoordinates();
    if (!mLastPerimeterPosition) {
        // First step around the perimeter, start on top
        return std::make_optional<Point2D>(
            centerCoordX, (centerCoordY - static_cast<int32_t>(mDistance) - 1));
    }

    const auto& [lastPositionCoordX, lastPositionCoordY]
        = mLastPerimeterPosition->getCoordinates();
    if ((lastPositionCoordY < centerCoordY)
        && (lastPositionCoordX >= centerCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX + 1,
            lastPositionCoordY + 1); // upper right, downwards
    } else if (
        (lastPositionCoordY >= centerCoordY)
        && (lastPositionCoordX > centerCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX - 1,
            lastPositionCoordY + 1); // lower right, downwards
    } else if (
        (lastPositionCoordY > centerCoordY)
        && (lastPositionCoordX <= centerCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX - 1,
            lastPositionCoordY - 1); // lower left, upwards
    } else if (
        (lastPositionCoordY <= centerCoordY)
        && (lastPositionCoordX < centerCoordX)) {
        if ((lastPositionCoordX + 1) == centerCoordX) {
            return std::nullopt; // circumference completed
        } else {
            return std::make_optional<Point2D>(
                lastPositionCoordX + 1,
                lastPositionCoordY - 1); // upper left, upwards
        }
    } else {
        assert(false);
        return std::nullopt;
    }
}

bool SquareDiamond2D::isOutside(const Point2D& point) const
{
    return Vector2D{ mCenter, point }.distance() > mDistance;
}

bool SquareDiamond2D::isInside(const Point2D& point) const
{
    return Vector2D{ mCenter, point }.distance() <= mDistance;
}

bool SquareDiamond2D::isInPerimeter(const Point2D& point) const
{
    return Vector2D{ mCenter, point }.distance() == mDistance;
}

std::vector<Point2D> SquareDiamond2D::getVertexes() const
{
    return { std::begin(mVertexes), std::end(mVertexes) };
}

uint32_t SquareDiamond2D::area() const
{
    return (mDistance * mDistance / 2) + 1U;
}

} // namespace utils::geometry2d
