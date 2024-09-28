#pragma once

#include "../Concepts.hpp"
#include "IShape2D.hpp"
#include "Operations2D.hpp"
#include "Point2D.hpp"
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
class Polygon2D : public IShape2D<T> {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  vertexes  List of vertexes of the shape, in sequential order
     *                       following the perimeter (clockwise or
     *                       counterclockwise).
     */
    Polygon2D(std::vector<Point2D<T>> const& vertexes)
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

private:
    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::vector<Point2D<T>> mVertexes;
};

} // namespace utils::geometry2d