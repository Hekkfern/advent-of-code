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
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Point2D& other) const;
    Point2D operator+(const Point2D& other) const;
    Point2D operator-() const;
    Point2D operator-(const Point2D& other) const;

private:
    int32_t mX = 0U;
    int32_t mY = 0U;
};

/**
 * @brief      Addition operator to move a Point2D according to a Vector2D.
 *
 * @param[in]  point2d   Original position.
 * @param[in]  vector2d   Vector of movement.
 */
Point2D operator+(const Point2D& point2d, const Vector2D& vector2d);

Point2D operator+(const Vector2D& vector2d, const Point2D& point2d);

} // namespace utils::geometry2d
