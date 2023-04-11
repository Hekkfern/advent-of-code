#pragma once

#include <cstdint>
#include <limits>

namespace utils::geometry2d {

class Point2D;
class Direction2D;

/**
 * @brief      This class describes a bounding box in 2D space.
 *
 * @details    In geometry, the minimum bounding box for a point set in N
 *             dimensions is the box with the smallest measure within which all
 *             the points lie.
 */
class BoundingBox2D {
public:
    /**
     * @brief      Updates the size of the bounding box to enclose this point
     *             too.
     *
     * @param[in]  point2D  The point to enclose.
     */
    void update(const Point2D& point2D);
    /**
     * @brief      Gets the minimum coordinate X.
     *
     * @return     The minimum coordinate X.
     */
    int32_t getMinX() const;
    /**
     * @brief      Gets the maximum coordinate X.
     *
     * @return     The maximum coordinate X.
     */
    int32_t getMaxX() const;
    /**
     * @brief      Gets the minimum coordinate X.
     *
     * @return     The minimum coordinate X.
     */
    int32_t getMinY() const;
    /**
     * @brief      Gets the maximum coordinate Y.
     *
     * @return     The maximum coordinate Y.
     */
    int32_t getMaxY() const;
    /**
     * @brief      Determines whether the specified point is outside of the
     *             bounding box.
     *
     * @warning    Being in the border (i.e. the perimeter) of the bounding box
     *             is considered as "being inside".
     *
     * @param[in]  point2D  The point to check.
     *
     * @return     True if the specified point is outside, False otherwise.
     */
    bool isOutside(const Point2D& point2D) const;
    /**
     * @brief      Determines whether the specified point is outside the
     *             bounding box for a given side of the box.
     *
     * @param[in]  point2D      The point to check.
     * @param[in]  direction2D  The side of the box. For example, the left side
     *                          of the box is @ref Direction2D::Left.
     *
     * @return     True if the specified point is outside, False otherwise.
     */
    bool isOutside(const Point2D& point2D, const Direction2D direction2D) const;

private:
    int32_t mMinX{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxX{ std::numeric_limits<int32_t>::min() };
    int32_t mMinY{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxY{ std::numeric_limits<int32_t>::min() };
};

} // namespace utils::geometry2d
