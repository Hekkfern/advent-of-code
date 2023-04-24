#pragma once

#include <cstdint>
#include <limits>

#include "Direction2D.hpp"
#include "Point2D.hpp"

namespace utils::geometry2d {

/**
 * @brief      This class describes a bounding box in 2D space.
 *
 * @details    In geometry, the minimum bounding box for a point set in N
 *             dimensions is the box with the smallest measure within which all
 *             the points lie.
 */
template <SignedIntegerType T = int32_t>
class BoundingBox2D {
public:
    /**
     * @brief      Updates the size of the bounding box to enclose this point
     *             too.
     *
     * @param[in]  point2D  The point to enclose.
     */
    void update(Point2D<T> const& point2D)
    {
        auto const x{point2D.getX()};
        auto const y{point2D.getY()};
        mMinX = std::min(mMinX, x);
        mMaxX = std::max(mMaxX, x);
        mMinY = std::min(mMinY, y);
        mMaxY = std::max(mMaxY, y);
    }
    /**
     * @brief      Gets the minimum coordinate X.
     *
     * @return     The minimum coordinate X.
     */
    [[nodiscard]] T getMinX() const { return mMinX; }
    /**
     * @brief      Gets the maximum coordinate X.
     *
     * @return     The maximum coordinate X.
     */
    [[nodiscard]] T getMaxX() const { return mMaxX; }
    /**
     * @brief      Gets the minimum coordinate X.
     *
     * @return     The minimum coordinate X.
     */
    [[nodiscard]] T getMinY() const { return mMinY; }
    /**
     * @brief      Gets the maximum coordinate Y.
     *
     * @return     The maximum coordinate Y.
     */
    [[nodiscard]] T getMaxY() const { return mMaxY; }
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
    [[nodiscard]] bool isOutside(Point2D<T> const& point2D) const
    {
        auto const x{point2D.getX()};
        auto const y{point2D.getY()};
        return (x > mMaxX) || (x < mMinX) || (y > mMaxY) || (y < mMinY);
    }
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
    [[nodiscard]] bool
    isOutside(Point2D<T> const& point2D, Direction2D direction2D) const
    {
        auto const x{point2D.getX()};
        auto const y{point2D.getY()};
        switch (direction2D) {
        case Direction2D::Up:
            return y > mMaxY;
        case Direction2D::Left:
            return x < mMinX;
        case Direction2D::Down:
            return y < mMinY;
        case Direction2D::Right:
            return x > mMaxX;
        default:
            return false;
        }
    }

private:
    T mMinX{std::numeric_limits<T>::max()};
    T mMaxX{std::numeric_limits<T>::min()};
    T mMinY{std::numeric_limits<T>::max()};
    T mMaxY{std::numeric_limits<T>::min()};
};

} // namespace utils::geometry2d
