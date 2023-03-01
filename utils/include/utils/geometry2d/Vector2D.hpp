#pragma once

#include <cstdint>
#include <memory>
#include <utility>

namespace utils::geometry2d {

class Point2D;

class Vector2D {
public:
    Vector2D();
    Vector2D(int32_t x, int32_t y);
    Vector2D(const Point2D& origin, const Point2D& destination);
    explicit Vector2D(const std::pair<int32_t, int32_t>& coords);
    std::pair<int32_t, int32_t> getCoordinates() const;
    int32_t getX() const;
    int32_t getY() const;
    std::pair<size_t, size_t> size() const;
    uint32_t distance() const;
    /**
     * @brief Modifies 2D vector so it's length becomes one, keeping same
     * direction
     */
    void normalize();
    Vector2D getNormalized() const;
    bool isZero() const;
    bool isHorizontal() const;
    bool isVertical() const;
    bool operator==(const Vector2D& other) const;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-() const;
    Vector2D operator-(const Vector2D& other) const;
    template <std::integral T> [[nodiscard]] static Vector2D create(T x, T y)
    {
        return Vector2D{ static_cast<int32_t>(x), static_cast<int32_t>(y) };
        ;
    }

private:
    int32_t mX = 0;
    int32_t mY = 0;
};

Vector2D operator*(const Vector2D& vector2D, const int32_t real);

Vector2D operator*(const int32_t real, const Vector2D& vector2D);

} // namespace utils::geometry2d

template <> struct std::hash<utils::geometry2d::Vector2D> {
    std::size_t operator()(const utils::geometry2d::Vector2D& k) const
    {
        return std::hash<int32_t>()(k.getX()) ^ std::hash<int32_t>()(k.getY());
    }
};