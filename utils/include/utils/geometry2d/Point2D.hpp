#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

namespace utils::geometry2d {

class Direction2D;
class Vector2D;

/**
 * @brief      This class describes a point in 2D space.
 */
class Point2D {
public:
    /**
     * @brief      Default constructor.
     */
    Point2D();
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    explicit Point2D(int32_t x, int32_t y);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Pair of coordinates (X,Y).
     */
    explicit Point2D(const std::pair<int32_t, int32_t>& coords);
    /**
     * @brief      Updates the position of this point to apply a unitary
     *             movement in the given direction.
     *
     * @param[in]  direction2D  The direction of the movement.
     */
    void move(Direction2D direction2D);
    /**
     * @brief      Updates the position of this point to apply a movement
     *             according to the given @ref Vector2D object.
     *
     * @param[in]  vector2D  The vector of the movement.
     */
    void move(const Vector2D& vector2D);
    /**
     * @brief      Calculates the point result of applying an arbtitrary movement to the
     *             selected point.
     *
     * @param[in]  point2d   The origin point.
     * @param[in]  vector2d  The vector of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D move(const Point2D& point2d, const Vector2D& vector2d);
    /**
     * @brief      Calculates the point result of applying an unitary movement
     *             towards the given direction to the selected point.
     *
     * @param[in]  point2d      The origin point.
     * @param[in]  direction2D  The direction of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D move(const Point2D& point2d, const Direction2D& direction2D);
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] std::pair<int32_t, int32_t> getCoordinates() const;
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] int32_t getX() const;
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] int32_t getY() const;
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(const Point2D& other) const;
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    [[nodiscard]] Point2D operator+(const Point2D& other) const;
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point2D operator-() const;
    /**
     * @brief      Subtraction operator.
     *
     * @param[in]  other  The other
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] Point2D operator-(const Point2D& other) const;
    /**
     * @brief      Factory method to create a new Point based on the selected
     *             coordinates.
     *
     * @param[in]  x     The coordinate X.
     * @param[in]  y     The coordinate Y.
     *
     * @tparam     T     Type of the coordinates.
     *
     * @return     New point.
     */
    template <std::integral T>
    [[nodiscard]] static Point2D create(T x, T y)
    {
        return Point2D{static_cast<int32_t>(x), static_cast<int32_t>(y)};
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Point2D& point2d);

    /**
     * Stores coordinate X.
     */
    int32_t mX = 0U;
    /**
     * Stores coordinate Y.
     */
    int32_t mY = 0U;
};

/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref Vector2D.
 *
 * @param[in]  point2d   Original position.
 * @param[in]  vector2d  Vector of movement.
 *
 * @return     The result of the movement.
 */
Point2D operator+(const Point2D& point2d, const Vector2D& vector2d);
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref Vector2D.
 *
 * @param[in]  vector2d  Vector of movement.
 * @param[in]  point2d   Original position.
 *
 * @return     The result of the movement.
 */
Point2D operator+(const Vector2D& vector2d, const Point2D& point2d);
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Direction2D.
 *
 * @param[in]  point2d      Original position.
 * @param[in]  direction2D  Direction of movement.
 *
 * @return     The result of the movement.
 */
Point2D operator+(const Point2D& point2d, const Direction2D& direction2D);
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Direction2D.
 *
 * @param[in]  direction2D  Direction of movement.
 * @param[in]  point2d      Original position.
 *
 * @return     The result of the movement.
 */
Point2D operator+(const Direction2D& direction2D, const Point2D& point2d);
/**
 * @brief      "Insert string into stream" operator.
 *
 * @param      os       The output stream.
 * @param[in]  point2d  The point.
 *
 * @return     The updated output stream.
 */
std::ostream& operator<<(std::ostream& os, const Point2D& point2d);

} // namespace utils::geometry2d

template <>
struct std::hash<utils::geometry2d::Point2D> {
    std::size_t operator()(const utils::geometry2d::Point2D& k) const noexcept
    {
        return std::hash<int32_t>()(k.getX()) ^ std::hash<int32_t>()(k.getY());
    }
};