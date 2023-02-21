#pragma once

#include <cstdint>
#include <utility>

namespace utils::geometry2d {

class Point2D;

class Vector2D {
public:
    Vector2D(int32_t x, int32_t y);
    Vector2D(const Point2D& origin, const Point2D& destination);
    Vector2D(const std::pair<int32_t, int32_t>& coords);
    std::pair<int32_t, int32_t> get() const;
    int32_t getX() const;
    int32_t getY() const;
    uint32_t distance() const;
    /**
     * @brief Modifies 2D vector so it's length becomes one, keeping same
     * direction
     */
    void normalize();
    Vector2D getNormalized() const;
    bool isZero() const;
    bool operator==(const Vector2D& other) const;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-() const;
    Vector2D operator-(const Vector2D& other) const;

private:
    int32_t mX;
    int32_t mY;
};

Vector2D operator*(const Vector2D& vector2D, const int32_t real);

Vector2D operator*(const int32_t real, const Vector2D& vector2D);

} // namespace utils::geometry2d
