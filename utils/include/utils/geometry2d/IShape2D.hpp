#pragma once

#include "Point2D.hpp"
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      This interface describes the common methods for all the shapes in
 *             2D space.
 */
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
    virtual std::vector<Point2D> getVertexes() const = 0;
    /**
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    virtual uint32_t area() const = 0;
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
    virtual bool isOutside(const Point2D& point) const = 0;
    /**
     * @brief      Determines whether the specified point is inside.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is inside, False otherwise.
     */
    virtual bool isInside(const Point2D& point) const = 0;
    /**
     * @brief      Determines whether the specified point is in perimeter.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is in perimeter, False otherwise.
     */
    virtual bool isInPerimeter(const Point2D& point) const = 0;
};

} // namespace utils::geometry2d
