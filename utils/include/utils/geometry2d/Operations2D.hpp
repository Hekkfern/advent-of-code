#pragma once

#include "../Concepts.hpp"
#include "Direction2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

namespace utils::geometry2d {

/**
 * @brief      Calculates the point result of applying an arbitrary movement
 *             to the selected point.
 *
 * @param[in]  origin    The origin point.
 * @param[in]  movement  The vector of the movement.
 *
 * @tparam     T     Type of the coordinate values.
 *
 * @return     Resulting position of the movement.
 */
template <SignedIntegerType T = int32_t>
[[maybe_unused]] [[nodiscard]] static Point2D<T>
move(Point2D<T> const& origin, Vector2D<T> const& movement)
{
    return Point2D{
        origin.getX() + movement.getX(), origin.getY() + movement.getY()};
}

/**
 * @brief      Converts the direction to an unitary @ref Vector2D object.
 *
 * @param[in]  direction  The direction to be converted.
 *
 * @tparam     T     Type of the coordinate values.
 *
 * @return     Vector2D representation of the direction.
 */
template <SignedIntegerType T = int32_t>
[[maybe_unused]] [[nodiscard]] static Vector2D<T>
toVector2D(Direction2D const& direction)
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

/**
 * @brief      Calculates the point result of applying an unitary movement
 *             towards the given direction to the selected point.
 *
 * @param[in]  origin     The origin point.
 * @param[in]  direction  The direction of the movement.
 *
 * @tparam     T     Type of the coordinate values.
 *
 * @return     Resulting position of the movement.
 */
template <SignedIntegerType T = int32_t>
[[maybe_unused]] [[nodiscard]] static Point2D<T>
move(Point2D<T> const& origin, Direction2D const& direction)
{
    return origin + toVector2D(direction);
}

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
[[maybe_unused]] [[nodiscard]] Point2D<T>
operator+(Point2D<T> const& origin, Vector2D<T> const& movement)
{
    return move(origin, movement);
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
[[maybe_unused]] [[nodiscard]] Point2D<T>
operator+(Vector2D<T> const& movement, Point2D<T> const& origin)
{
    return move(origin, movement);
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
[[maybe_unused]]
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
[[maybe_unused]] [[nodiscard]] Point2D<T>
operator+(Point2D<T> const& origin, Direction2D const& direction)
{
    return move(origin, direction);
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
[[maybe_unused]] [[nodiscard]] Point2D<T>
operator+(Direction2D const& direction, Point2D<T> const& origin)
{
    return move(origin, direction);
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
[[maybe_unused]]
void operator+=(Point2D<T>& point, Direction2D const& direction)
{
    point = point + direction;
}

} // namespace utils::geometry2d
