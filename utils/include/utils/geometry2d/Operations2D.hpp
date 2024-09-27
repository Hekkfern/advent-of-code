#pragma once

#include "../Concepts.hpp"
#include "Direction2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <numbers>

namespace utils::geometry2d {

/**
 * @brief      Implements several common operations between elements of a
 *             2-dimension system.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Operations2D {
public:
    /**
     * @brief      Calculates the point result of applying an arbitrary movement
     *             to the selected point.
     *
     * @param[in]  origin    The origin point.
     * @param[in]  movement  The vector of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D<T>
    move(Point2D<T> const& origin, Vector2D<T> const& movement)
    {
        return Point2D{
            origin.getX() + movement.getX(), origin.getY() + movement.getY()};
    }
    /**
     * @brief      Calculates the point result of applying an unitary movement
     *             towards the given direction to the selected point.
     *
     * @param[in]  origin     The origin point.
     * @param[in]  direction  The direction of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D<T>
    move(Point2D<T> const& origin, Direction2D const& direction)
    {
        return origin + toVector2D(direction);
    }
    /**
     * @brief      Converts the direction to an unitary @ref Vector2D object.
     *
     * @param[in]  direction  The direction to be converted.
     *
     * @return     Vector2D representation of the direction.
     */
    [[nodiscard]] static Vector2D<T> toVector2D(Direction2D const& direction)
    {
        T coordX{0};
        T coordY{0};
        switch (direction.getValue()) {
        case Direction2D::Left:
        case Direction2D::DownLeft:
        case Direction2D::UpLeft:
            --coordX;
            break;
        case Direction2D::Right:
        case Direction2D::UpRight:
        case Direction2D::DownRight:
            ++coordX;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        switch (direction.getValue()) {
        case Direction2D::Down:
        case Direction2D::DownRight:
        case Direction2D::DownLeft:
            --coordY;
            break;
        case Direction2D::Up:
        case Direction2D::UpRight:
        case Direction2D::UpLeft:
            ++coordY;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        return Vector2D<T>{coordX, coordY};
    }
};

/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Vector2D.
 *
 * @param[in]  origin    Original position.
 * @param[in]  movement  Vector of movement.
 *
 * @tparam     T         Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point2D<T>
operator+(Point2D<T> const& origin, Vector2D<T> const& movement)
{
    return Operations2D<T>::move(origin, movement);
}
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Vector2D.
 *
 * @param[in]  movement  Vector of movement.
 * @param[in]  origin    Original position.
 *
 * @tparam     T         Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point2D<T>
operator+(Vector2D<T> const& movement, Point2D<T> const& origin)
{
    return Operations2D<T>::move(origin, movement);
}
/**
 * @brief      Addition assignment operator to move a @ref Point2D according to
 *             a @ref Vector2D.
 *
 * @param[in]  point     Original position.
 * @param[in]  movement  Vector of movement.
 *
 * @tparam     T         Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
void operator+=(Point2D<T>& point, Vector2D<T> const& movement)
{
    point = point + movement;
}
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Direction2D.
 *
 * @param[in]  origin     Original position.
 * @param[in]  direction  Direction of movement.
 *
 * @tparam     T          Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point2D<T>
operator+(Point2D<T> const& origin, Direction2D const& direction)
{
    return Operations2D<T>::move(origin, direction);
}
/**
 * @brief      Addition operator to move a @ref Point2D according to a @ref
 *             Direction2D.
 *
 * @param[in]  direction  Direction of movement.
 * @param[in]  origin     Original position.
 *
 * @tparam     T          Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point2D<T>
operator+(Direction2D const& direction, Point2D<T> const& origin)
{
    return Operations2D<T>::move(origin, direction);
}
/**
 * @brief         Addition assignment operator to move a @ref Point2D according
 *                to a @ref Direction2D.
 *
 * @param[in,out] point      Position to move.
 * @param[in]     direction  Direction of movement.
 *
 * @tparam        T          Type of the coordinates.
 */
template <SignedIntegerType T = int32_t>
void operator+=(Point2D<T>& point, Direction2D const& direction)
{
    point = point + direction;
}

/**
 * @brief      Applies the "Shoelace formula"
 *             (https://en.wikipedia.org/wiki/Shoelace_formula), a mathematical
 *             algorithm to determine the area of a simple polygon whose
 *             vertices are described by their Cartesian coordinates in the
 *             place.
 *
 * @param[in]  perimeterPoints  List of all the points forming the perimeter of
 *                              the polygon, ordered in a counter-clock-wise or
 *                              clock-wise sequence.
 *
 * @tparam     T                Type of the coordinates.
 *
 * @return     Area of the shape.
 */
template <SignedIntegerType T = int32_t>
double calculateArbitraryPolygonArea(std::vector<Point2D<T>> perimeterPoints)
{
    T leftSum{0};
    T rightSum{0};

    for (std::size_t i{0ULL}; i < perimeterPoints.size(); ++i) {
        std::size_t j{(i + 1ULL) % perimeterPoints.size()};
        leftSum += perimeterPoints[i].getX() * perimeterPoints[j].getY();
        rightSum += perimeterPoints[j].getX() * perimeterPoints[i].getY();
    }

    return 0.5 * std::abs(leftSum - rightSum);
}

/**
 * @brief      Applies "Pick's theorem"
 *             (https://en.wikipedia.org/wiki/Pick%27s_theorem), a formula for
 *             the area of a simple polygon with integer vertex coordinates, to
 *             find the number of integer points interior to the polygon.
 *
 * @param[in]  perimeterPoints  List of all the points forming the perimeter of
 *                              the polygon, ordered in a counter-clock-wise or
 *                              clock-wise sequence.
 *
 * @tparam     T                Type of the coordinates.
 *
 * @return     Number of points in the interior of the polygon.
 */
template <SignedIntegerType T = int32_t>
std::size_t calculateNumberOfIntrinsicPointsInsidePolygon(
    std::vector<Point2D<T>> perimeterPoints)
{
    auto const area{calculateArbitraryPolygonArea(perimeterPoints)};
    return static_cast<std::size_t>(
        area - (static_cast<double>(perimeterPoints.size()) / 2.0) + 1.0);
}

/**
 * @brief      Return the angle between two vectors defined by the origin and an
 *             arbitrary point.
 *
 * @param[in]  p1    The first point.
 * @param[in]  p2    The second point.
 *
 * @tparam     T     Type of the coordinates.
 *
 * @return     Angle between the two vectors. The angle is from vector 1 to
 *             vector 2, positive anticlockwise. The result is between -pi ->
 *             pi.
 */
template <SignedIntegerType T = int32_t>
double calculateAngleBetweenTwoPointsFromOrigin(
    Point2D<T> const& p1, Point2D<T> const& p2) noexcept
{
    return calculateAngleBetweenTwoVectors(Vector2D<T>{p1}, Vector2D<T>{p2});
}

/**
 * @brief      Calculates the angle between two arbitrary vectors.
 *
 * @param[in]  v1    The first vector.
 * @param[in]  v2    The second vector.
 *
 * @tparam     T     Type of the coordinates.
 *
 * @return     Angle between the two vectors. The angle is from vector 1 to
 *             vector 2, positive anticlockwise. The result is between -pi ->
 *             pi.
 */
template <SignedIntegerType T = int32_t>
double calculateAngleBetweenTwoVectors(
    Vector2D<T> const& v1, Vector2D<T> const& v2) noexcept
{
    static constexpr double PI{std::numbers::pi};
    static constexpr double TWOPI{2 * PI};

    double const theta1{v1.angle()};
    double const theta2{v2.angle()};
    double diffTheta{theta2 - theta1};
    while (diffTheta > PI) {
        diffTheta -= TWOPI;
    }
    while (diffTheta < -PI) {
        diffTheta += TWOPI;
    }
    return diffTheta;
}

} // namespace utils::geometry2d
