#pragma once

#include "IShape2D.hpp"
#include "Operations2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      Describes a Rectangle shape in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
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
        Point2D<T> const& bottomLeft, Point2D<T> const& topRight)
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
        Point2D<T> const& bottomLeft, Vector2D<T> const& diagonal)
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
        Point2D<T> const& bottomLeft, uint32_t width, uint32_t height)
        : mVertexes{{bottomLeft, bottomLeft + Vector2D<T>{static_cast<T>(width), 0}, bottomLeft + Vector2D<T>{static_cast<T>(width), static_cast<T>(height)}, bottomLeft + Vector2D<T>{0, static_cast<T>(height)}}}
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
    [[nodiscard]] std::array<uint64_t, 2U> size() const
    {
        return {mWidth, mHeight};
    }
    /**
     * @copydoc IShape::area
     */
    [[nodiscard]] uint64_t area() const noexcept override
    {
        return static_cast<uint64_t>(mWidth) * static_cast<uint64_t>(mHeight);
    }
    /**
     * @copydoc IShape::isOutside
     */
    [[nodiscard]] bool
    isOutside(Point2D<T> const& point) const noexcept override
    {
        return !isInside(point);
    }
    /**
     * @copydoc IShape::isInside
     */
    [[nodiscard]] bool isInside(Point2D<T> const& point) const noexcept override
    {
        auto const& bottomLeft{getBottomLeftPoint()};
        auto const& topRight{getTopRightPoint()};
        return bottomLeft.getX() <= point.getX()
            && point.getX() <= topRight.getX()
            && bottomLeft.getY() <= point.getY()
            && point.getY() <= topRight.getY();
    }
    /**
     * @copydoc IShape::isInPerimeter
     */
    [[nodiscard]] bool
    isInPerimeter(Point2D<T> const& point) const noexcept override
    {
        Vector2D const v1{getBottomLeftPoint(), point};
        Vector2D const v2{getTopRightPoint(), point};
        return v1.is() == Vector2DType::Vertical
            || v1.is() == Vector2DType::Horizontal
            || v2.is() == Vector2DType::Vertical
            || v2.is() == Vector2DType::Horizontal;
    }
    /**
     * @copydoc IShape::getVertexes
     */
    [[nodiscard]] std::vector<Point2D<T>> getVertexes() const noexcept override
    {
        return {std::begin(mVertexes), std::end(mVertexes)};
    }
    /**
     * @brief      Gets the width.
     *
     * @return     The width.
     */
    [[nodiscard]] uint32_t getWidth() const { return mWidth; }
    /**
     * @brief      Gets the height.
     *
     * @return     The height.
     */
    [[nodiscard]] uint32_t getHeight() const { return mHeight; }

private:
    /**
     * @brief      Calculates the bottom left point of this shape.
     *
     * @return     The bottom left point.
     */
    [[nodiscard]] Point2D<T> const& getBottomLeftPoint() const
    {
        return mVertexes.at(0);
    }
    /**
     * @brief      Calculates the top right point of this shape.
     *
     * @return     The top right point.
     */
    [[nodiscard]] Point2D<T> const& getTopRightPoint() const
    {
        return mVertexes.at(2);
    }

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
