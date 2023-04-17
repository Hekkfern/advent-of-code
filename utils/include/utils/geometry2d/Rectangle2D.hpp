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
template <SignedIntegerType T = int32_t>
class Rectangle2D : public IShape2D<T> {
public:
    /**
     * Number of vertexes of a Rectangle.
     */
    static constexpr uint32_t NumberOfVertexes{4U};

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  topRight    The top right point.
     */
    explicit Rectangle2D(
        const Point2D<T>& bottomLeft, const Point2D<T>& topRight)
        : Rectangle2D{bottomLeft, Vector2D{bottomLeft, topRight}}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  diagonal    The diagonal vector from the bottom left point to
     *                         the top right point.
     */
    explicit Rectangle2D(
        const Point2D<T>& bottomLeft, const Vector2D<T>& diagonal)
        : Rectangle2D{
            bottomLeft,
            static_cast<uint32_t>(diagonal.size()[0]),
            static_cast<uint32_t>(diagonal.size()[1])}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  bottomLeft  The bottom left point.
     * @param[in]  width       The width of the shape.
     * @param[in]  height      The height of the shape.
     */
    explicit Rectangle2D(
        const Point2D<T>& bottomLeft, uint32_t width, uint32_t height)
        : mVertexes{{bottomLeft, bottomLeft + Vector2D{static_cast<T>(width), 0}, bottomLeft + Vector2D{static_cast<T>(width), static_cast<T>(height)}, bottomLeft + Vector2D{0, static_cast<T>(height)}}}
        , mWidth{width}
        , mHeight{height}
    {
    }
    /**
     * @brief      Gets the size of the shape, in terms of width and height.
     *
     * @return     Pair of values, representing the width and height,
     *             respectively.
     */
    std::array<uint64_t, 2U> size() const { return {mWidth, mHeight}; }
    /**
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    uint64_t area() const override
    {
        return static_cast<uint64_t>(mWidth) * static_cast<uint64_t>(mHeight);
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
    bool isOutside(const Point2D<T>& point) const override
    {
        return !isInside(point);
    }
    /**
     * @brief      Determines whether the specified point is inside.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is inside, False otherwise.
     */
    bool isInside(const Point2D<T>& point) const override
    {
        const auto& bottomLeft{getBottomLeftPoint()};
        const auto& topRight{getTopRightPoint()};
        return (bottomLeft.getX() <= point.getX())
            && (point.getX() <= topRight.getX())
            && (bottomLeft.getY() <= point.getY())
            && (point.getY() <= topRight.getY());
    }
    /**
     * @brief      Determines whether the specified point is in perimeter.
     *
     * @param[in]  point  The point to check.
     *
     * @return     True if the specified point is in perimeter, False otherwise.
     */
    bool isInPerimeter(const Point2D<T>& point) const override
    {
        const Vector2D v1{getBottomLeftPoint(), point};
        const Vector2D v2{getTopRightPoint(), point};
        return v1.isVertical() || v1.isHorizontal() || v2.isVertical()
            || v2.isHorizontal();
    }
    /**
     * @brief      Gets the vertexes of the shape.
     *
     * @return     List of vertexes.
     */
    std::vector<Point2D<T>> getVertexes() const override
    {
        return {std::begin(mVertexes), std::end(mVertexes)};
    }
    /**
     * @brief      Gets the width.
     *
     * @return     The width.
     */
    uint32_t getWidth() const { return mWidth; }
    /**
     * @brief      Gets the height.
     *
     * @return     The height.
     */
    uint32_t getHeight() const { return mHeight; }

private:
    /**
     * @brief      Calculates the bottom left point of this shape.
     *
     * @return     The bottom left point.
     */
    const Point2D<T>& getBottomLeftPoint() const { return mVertexes.at(0); }
    /**
     * @brief      Calculates the top right point of this shape.
     *
     * @return     The top right point.
     */
    const Point2D<T>& getTopRightPoint() const { return mVertexes.at(2); }

    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::array<Point2D<T>, NumberOfVertexes> mVertexes;
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
