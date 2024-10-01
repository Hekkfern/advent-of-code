#pragma once

#include "Calculations2D.hpp"
#include "IShape2D.hpp"
#include "OrthogonalLine2D.h"
#include "Point2D.hpp"
#include "utils/Concepts.hpp"
#include <cmath>
#include <numbers>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      Class for a 2D polygon.
 *
 * @tparam T Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class OrthogonalPolygon2D : public IShape2D<T> {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertexes  List of vertexes of the shape, in sequential order
     *                       following the perimeter (clockwise or
     *                       counterclockwise).
     */
    OrthogonalPolygon2D(std::vector<Point2D<T>> const& vertexes)
        : mVertexes{vertexes}
    {
    }
    /**
     * @copydoc IShape::getVertexes
     */
    [[nodiscard]] std::vector<Point2D<T>> getVertexes() const noexcept override
    {
        return mVertexes;
    }
    /**
     * @copydoc IShape::area
     */
    [[nodiscard]] uint64_t area() const noexcept override
    {
        return calculateArbitraryPolygonArea(mVertexes);
    }
    /**
     * @copydoc IShape::isOutside
     */
    [[nodiscard]] bool
    isOutside(Point2D<T> const& point) const noexcept override
    {
        return !isInside(point) && !isInPerimeter(point);
    }
    /**
     * @copydoc IShape::isInside
     */
    [[nodiscard]] bool isInside(Point2D<T> const& point) const noexcept override
    {
        // https://en.wikipedia.org/wiki/Point_in_polygon#Winding_number_algorithm

        double angle{0.0};
        std::size_t const n{mVertexes.size()};
        for (std::size_t i{0ULL}; i < n; i++) {
            Vector2D<T> const v1{mVertexes[i], point};
            Vector2D<T> const v2{mVertexes[(i + 1) % n], point};
            angle += calculateAngleBetweenTwoVectors(v1, v2);
        }
        return std::abs(angle) >= std::numbers::pi;
    }
    /**
     * @copydoc IShape::isInPerimeter
     */
    [[nodiscard]] bool
    isInPerimeter(Point2D<T> const& point) const noexcept override
    {
        // TODO
        (void)point;
        return false;
    }
    /**
     * @brief Calculates the number of intrinsic points inside this shape.
     *
     * @return Number of intrinsic points.
     */
    [[nodiscard]] uint64_t calculateNumberOfIntrinsicPoints() const noexcept
    {
        return calculateNumberOfIntrinsicPointsInsidePolygon(
            calculateBoundaryPoints());
    }
    /**
     * @brief Calculates the perimeter length of this shape.
     *
     * @return Perimeter length.
     */
    [[nodiscard]] uint64_t perimeter() const noexcept
    {
        uint64_t length{0ULL};
        std::size_t const n{mVertexes.size()};
        for (std::size_t index{0ULL}; index < n; ++index) {
            auto nextIndex{(index + 1ULL) % n};
            length
                += Vector2D{mVertexes[nextIndex], mVertexes[index]}.distance();
        }
        return length;
    }
    /**
     * @brief      Calculates the boundary points of this shape.
     *
     * @details Given a list of vertexes of the shape, this method calculates
     * all the points forming its perimeter. It means that it will return all
     * the vertexes, plus all the points between them.
     *
     * @return     List of boundary points. It doesn't contain repeated points.
     */
    std::vector<Point2D<T>> calculateBoundaryPoints() const noexcept
    {
        std::vector<Point2D<T>> points;
        std::size_t const n{mVertexes.size()};
        for (std::size_t index{0ULL}; index < n; ++index) {
            auto nextIndex{(index + 1ULL) % n};
            /* get unary vector of movement */
            Vector2D<T> const vector{mVertexes[index], mVertexes[nextIndex]};
            auto const unaryVector{vector.normalize()};
            /* get points */
            Point2D currentPoint{mVertexes[index]};
            while (currentPoint != mVertexes[nextIndex]) {
                currentPoint += unaryVector;
                points.emplace_back(currentPoint);
            }
        }
        return points;
    }

private:
    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::vector<Point2D<T>> mVertexes;
};

} // namespace utils::geometry2d
