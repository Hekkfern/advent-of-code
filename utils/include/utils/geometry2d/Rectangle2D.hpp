#pragma once

#include "IShape2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      This class describes a Rectangle shape in 2D space.
 */
class Rectangle2D : public IShape2D {
public:
    /**
     * Number of vertexes of a Rectangle.
     */
    static constexpr uint32_t NumberOfVertexes{ 4U };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  topRight    The top right point.
     */
    explicit Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  diagonal    The diagonal vector from the bottom left point to
     *                         the top right point.
     */
    explicit Rectangle2D(
        const utils::geometry2d::Point2D& bottomLeft,
        const Vector2D& diagonal);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  width       The width of the shape.
     * @param[in]  height      The height of the shape.
     */
    explicit Rectangle2D(const Point2D& bottomLeft, uint32_t width, uint32_t height);
    /**
     * @brief      Gets the size of the shape, in terms of width and height.
     *
     * @return     Pair of values, represeting the width and height,
     *             respectively.
     */
    std::pair<size_t, size_t> size() const;
    /**
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    uint32_t area() const override;
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
    bool isOutside(const Point2D& point) const override;
    /**
     * @brief      Determines whether the specified point is inside.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is inside, False otherwise.
     */
    bool isInside(const Point2D& point) const override;
    /**
     * @brief      Determines whether the specified point is in perimeter.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is in perimeter, False otherwise.
     */
    bool isInPerimeter(const Point2D& point) const override;
    /**
     * @brief      Gets the vertexes of the shape.
     *
     * @return     List of vertexes.
     */
    std::vector<Point2D> getVertexes() const override;
    /**
     * @brief      Gets the width.
     *
     * @return     The width.
     */
    uint32_t getWidth() const;
    /**
     * @brief      Gets the height.
     *
     * @return     The height.
     */
    uint32_t getHeight() const;

private:
    /**
     * @brief      Calculates the bottom left point of this shape.
     *
     * @return     The bottom left point.
     */
    const Point2D& getBottomLeftPoint() const;
    /**
     * @brief      Calculates the top right point of this shape.
     *
     * @return     The top right point.
     */
    const Point2D& getTopRightPoint() const;

    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::array<Point2D, NumberOfVertexes> mVertexes;
    /**
     * Stores the width
     */
    uint32_t mWidth;
    /**
     * Stores the height.
     */
    uint32_t mHeight;
};

} // namespace utils::geometry2d
