#pragma once

#include <cstdint>
#include <utility>

namespace utils::geometry2d {

class Direction2D;
class Vector2D;

class Point2D {
public:
    Point2D();
    Point2D(int32_t x, int32_t y);
    void move(Direction2D direction);
    void move(const Vector2D& vector);
    std::pair<int32_t, int32_t> get() const;
    int32_t getX() const;
    int32_t getY() const;

private:
    /**
     * Friend relationship of the equality operator overload.
     */
    friend bool operator==(const Point2D& lhs, const Point2D& rhs);

    int32_t mX = 0U;
    int32_t mY = 0U;
};

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the equality.
 */
bool operator==(const Point2D& lhs, const Point2D& rhs);

/**
 * @brief      Inequality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the inequality.
 */
bool operator!=(const Point2D& lhs, const Point2D& rhs);

} // namespace utils::geometry2d
