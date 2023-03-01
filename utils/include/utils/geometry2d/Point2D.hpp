#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

namespace utils::geometry2d {

class Direction2D;
class Vector2D;

class Point2D {
public:
    Point2D();
    Point2D(int32_t x, int32_t y);
    explicit Point2D(const std::pair<int32_t, int32_t>& coords);
    void move(Direction2D direction2D);
    void move(const Vector2D& vector2D);
    static Point2D move(const Point2D& point2d, const Vector2D& vector2d);
    static Point2D move(const Point2D& point2d, const Direction2D& direction2D);
    std::pair<int32_t, int32_t> getCoordinates() const;
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
    template <std::integral T> [[nodiscard]] static Point2D create(T x, T y)
    {
        return Point2D{ static_cast<int32_t>(x), static_cast<int32_t>(y) };
    }

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

Point2D operator+(const Point2D& point2d, const Direction2D& direction2D);

Point2D operator+(const Direction2D& direction2D, const Point2D& point2d);

} // namespace utils::geometry2d

template <> struct std::hash<utils::geometry2d::Point2D> {
    std::size_t operator()(const utils::geometry2d::Point2D& k) const
    {
        return std::hash<int32_t>()(k.getX()) ^ std::hash<int32_t>()(k.getY());
    }
};