#pragma once

#include "IShape2D.hpp"
#include "Operations2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      Describes a Square Diamond shape in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class SquareDiamond2D : public IShape2D<T> {
public:
    /**
     * Number of vertexes of a Rectangle.
     */
    static constexpr uint32_t NumberOfVertexes{4U};

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  centerPoint     The center point.
     * @param[in]  perimeterPoint  Any perimeter point.
     */
    explicit SquareDiamond2D(
        Point2D<T> const& centerPoint, Point2D<T> const& perimeterPoint)
        : SquareDiamond2D{
              centerPoint, Vector2D{centerPoint, perimeterPoint}.distance()}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  centerPoint  The center point.
     * @param[in]  distance     The distance from the center to the perimeter.
     */
    explicit SquareDiamond2D(
        Point2D<T> const& centerPoint, uint64_t const distance)
        : mCenter{centerPoint}
        , mDistance{distance}
        , mVertexes{
              centerPoint + Vector2D{0, static_cast<T>(distance)},
              centerPoint + Vector2D{static_cast<T>(distance), 0},
              centerPoint + Vector2D{0, -static_cast<T>(distance)},
              centerPoint + Vector2D{-static_cast<T>(distance), 0}}
    {
    }
    /**
     * @brief      Gets the central point.
     *
     * @return     The central point.
     */
    [[nodiscard]] Point2D<T> const& getCenter() const { return mCenter; }
    /**
     * @brief      Gets the vertexes of the shape.
     *
     * @return     List of vertexes.
     */
    [[nodiscard]] std::vector<Point2D<T>> getVertexes() const override
    {
        return {std::begin(mVertexes), std::end(mVertexes)};
    }
    /**
     * @brief      Gets the distance from the center to the perimeter.
     *
     * @return     The distance from the center to the perimeter.
     */
    [[nodiscard]] uint64_t getDistance() const { return mDistance; }
    /**
     * @brief      Returns the next point going through the border of the shape,
     *             which is outside.
     *
     * @warning    It is an iterative method, which means that it remembers the
     *             previous call to continue iterating.
     *
     * @todo       Use C++20 coroutines.
     *
     * @return     Next point of the closes point to the perimeter from the
     *             outside, or std::nullopt if a whole loop has been completed.
     */
    [[nodiscard]] std::optional<Point2D<T>> stepAroundOutside()
    {
        std::optional<Point2D<T>> nextPoint;
        auto const& [centerCoordX, centerCoordY] = mCenter.getCoordinates();
        if (!mLastPerimeterPosition) {
            // First step around the perimeter, start on top
            nextPoint = std::make_optional<Point2D<T>>(
                centerCoordX, (centerCoordY + static_cast<T>(mDistance) + 1));
        } else {
            auto const& [lastPositionCoordX, lastPositionCoordY]
                = mLastPerimeterPosition->getCoordinates();
            if ((lastPositionCoordY > centerCoordY)
                && (lastPositionCoordX >= centerCoordX)) {
                // upper right quadrant. go downwards
                nextPoint = std::make_optional<Point2D<T>>(
                    lastPositionCoordX + 1, lastPositionCoordY - 1);
            } else if (
                (lastPositionCoordY <= centerCoordY)
                && (lastPositionCoordX > centerCoordX)) {
                // lower right quadrant. go downwards
                nextPoint = std::make_optional<Point2D<T>>(
                    lastPositionCoordX - 1, lastPositionCoordY - 1);
            } else if (
                (lastPositionCoordY < centerCoordY)
                && (lastPositionCoordX <= centerCoordX)) {
                // lower left quadrant. go upwards
                nextPoint = std::make_optional<Point2D<T>>(
                    lastPositionCoordX - 1, lastPositionCoordY + 1);
            } else if (
                (lastPositionCoordY >= centerCoordY)
                && (lastPositionCoordX < centerCoordX)) {
                if ((lastPositionCoordX + 1) == centerCoordX) {
                    // circumference completed
                    nextPoint = std::nullopt;
                } else {
                    // upper left quadrant. go upwards
                    nextPoint = std::make_optional<Point2D<T>>(
                        lastPositionCoordX + 1, lastPositionCoordY + 1);
                }
            } else {
                return std::nullopt;
            }
        }
        mLastPerimeterPosition = nextPoint;
        return nextPoint;
    }
    /**
     * @brief      Determines whether the specified point is outside.
     *
     * @warning    Being in the border (i.e. the perimeter) of the bounding box
     *             is considered as "not being outside".
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is outside, False otherwise.
     */
    [[nodiscard]] bool isOutside(Point2D<T> const& point) const override
    {
        return Vector2D{mCenter, point}.distance() > mDistance;
    }
    /**
     * @brief      Determines whether the specified point is inside.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is inside, False otherwise.
     */
    [[nodiscard]] bool isInside(Point2D<T> const& point) const override
    {
        return Vector2D{mCenter, point}.distance() <= mDistance;
    }
    /**
     * @brief      Determines whether the specified point is in perimeter.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is in perimeter, False otherwise.
     */
    [[nodiscard]] bool isInPerimeter(Point2D<T> const& point) const override
    {
        return Vector2D{mCenter, point}.distance() == mDistance;
    }
    /**
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    [[nodiscard]] uint64_t area() const override
    {
        uint64_t const diagonalLength{(2U * mDistance) + 1U};
        return ((diagonalLength * diagonalLength) / 2U) + 1U;
    }

private:
    /**
     * Stores the central point of the shape.
     */
    Point2D<T> mCenter;
    /**
     * Stores the distance from the center to the perimeter.
     */
    uint64_t mDistance;
    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::array<Point2D<T>, NumberOfVertexes> mVertexes;
    /**
     * Stores the last position of the execution of @ref stepAroundOutside
     * method.
     */
    std::optional<Point2D<T>> mLastPerimeterPosition{};
};

} // namespace utils::geometry2d
