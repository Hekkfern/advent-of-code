#pragma once

#include "IShape2D.hpp"
#include "Point2D.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace utils::geometry2d {

/**
 * @brief      This class describes a Square Diamond shape in 2D space.
 */
class SquareDiamond2D : public IShape2D {
public:
    /**
     * Number of vertexes of a Rectangle.
     */
    static constexpr uint32_t NumberOfVertexes{ 4U };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  centerPoint     The center point.
     * @param[in]  perimeterPoint  Any perimeter point.
     */
    explicit SquareDiamond2D(const Point2D& centerPoint, const Point2D& perimeterPoint);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  centerPoint  The center point.
     * @param[in]  distance     The distance from the center to the perimeter.
     */
    explicit SquareDiamond2D(const Point2D& centerPoint, uint32_t distance);
    /**
     * @brief      Gets the central point.
     *
     * @return     The central point.
     */
    const Point2D& getCenter() const;
    /**
     * @brief      Gets the vertexes of the shape.
     *
     * @return     List of vertexes.
     */
    std::vector<Point2D> getVertexes() const override;
    /**
     * @brief      Gets the distance from the center to the perimeter.
     *
     * @return     The distance from the center to the perimeter.
     */
    uint32_t getDistance() const;
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
    std::optional<Point2D> stepAroundOutside();
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
     * @brief      Calculates the area.
     *
     * @return     Area of the shape.
     */
    uint32_t area() const override;

private:
    /** 
     * Stores the central point of the shape. 
     */
    Point2D mCenter;
    /**
     * Stores the distance from the center to the perimeter.
     */
    uint32_t mDistance;
    /**
     * Stores the vertexes (points 2D) of this shape.
     */
    std::array<Point2D, NumberOfVertexes> mVertexes;
    /**
     * Stores the last position of the execution of @ref stepAroundOutside
     * method.
     */
    std::optional<Point2D> mLastPerimeterPosition{};
};

} // namespace utils::geometry2d
