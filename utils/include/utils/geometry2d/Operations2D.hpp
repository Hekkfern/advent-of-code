#pragma once

#include <cstdint>

namespace utils::geometry2d {

class Point2D;
class Vector2D;

// ------------ Point2D operations ------------

/**
 * @brief      Addition operator to move a Point2D according to a Vector2D.
 *
 * @param[in]  point2d   Original position.
 * @param[in]  vector2d   Vector of movement.
 */
Point2D operator+(const Point2D& point2d, const Vector2D& vector2d);

Point2D operator+(const Vector2D& vector2d, const Point2D& point2d);

// ------------ Vector2D operations ------------

Vector2D operator*(const Vector2D& vector2D, const int32_t real);

Vector2D operator*(const int32_t real, const Vector2D& vector2D);

} // namespace utils::geometry2d