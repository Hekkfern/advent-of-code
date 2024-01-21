#pragma once

#include "Point2D.hpp"
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      Describes an interface with the common methods for all the shapes
 *             in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class IShape2D {
public:
    /**
     * @brief      Destroys the object.
     */
    virtual ~IShape2D() = default;
    /**
     * @brief      Gets the vertexes of the shape.
     *
     * @return     List of vertexes.
     */
    [[nodiscard]] virtual std::vector<Point2D<T>> getVertexes() const = 0;
    /**
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    [[nodiscard]] virtual uint64_t area() const = 0;
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
    [[nodiscard]] virtual bool isOutside(Point2D<T> const& point) const = 0;
    /**
     * @brief      Determines whether the specified point is inside.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is inside, False otherwise.
     */
    [[nodiscard]] virtual bool isInside(Point2D<T> const& point) const = 0;
    /**
     * @brief      Determines whether the specified point is in perimeter.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is in perimeter, False otherwise.
     */
    [[nodiscard]] virtual bool isInPerimeter(Point2D<T> const& point) const = 0;
};

} // namespace utils::geometry2d
