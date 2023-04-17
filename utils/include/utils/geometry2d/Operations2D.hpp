#pragma once

#include "../Concepts.hpp"
#include "Direction2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

namespace utils::geometry2d {

template <SignedIntegerType T = int32_t>
class Operations2D {
public:
    /**
     * @brief      Calculates the point result of applying an arbitrary
     * movement to the selected point.
     *
     * @param[in]  origin      The origin point.
     * @param[in]  movement  The vector of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D<T>
    move(const Point2D<T>& origin, const Vector2D<T>& movement)
    {
        return Point2D{
            origin.getX() + movement.getX(), origin.getY() + movement.getY()};
    }
    /**
     * @brief      Calculates the point result of applying an unitary movement
     *             towards the given direction to the selected point.
     *
     * @param[in]  origin      The origin point.
     * @param[in]  direction  The direction of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] static Point2D<T>
    move(const Point2D<T>& origin, const Direction2D& direction)
    {
        // TODO
    }
    /**
     * @brief      Addition operator to move a @ref Point2D according to a @ref
     * Vector2D.
     *
     * @param[in]  origin   Original position.
     * @param[in]  movement  Vector of movement.
     *
     * @return     The result of the movement.
     */
    [[nodiscard]] static Point2D<T>
    operator+(const Point2D<T>& origin, const Vector2D<T>& movement)
    {
        return move(origin, movement);
    }
    /**
     * @brief      Addition operator to move a @ref Point2D according to a @ref
     * Vector2D.
     *
     * @param[in]  movement  Vector of movement.
     * @param[in]  origin   Original position.
     *
     * @return     The result of the movement.
     */
    [[nodiscard]] static Point2D<T>
    operator+(const Vector2D<T>& movement, const Point2D<T>& origin)
    {
        return move(origin, movement);
    }
    /**
     * @brief      Addition operator to move a @ref Point2D according to a @ref
     *             Direction2D.
     *
     * @param[in]  origin      Original position.
     * @param[in]  direction  Direction of movement.
     *
     * @return     The result of the movement.
     */
    [[nodiscard]] static Point2D<T>
    operator+(const Point2D<T>& origin, const Direction2D& direction)
    {
        // TODO
    }
    /**
     * @brief      Addition operator to move a @ref Point2D according to a @ref
     *             Direction2D.
     *
     * @param[in]  direction  Direction of movement.
     * @param[in]  origin      Original position.
     *
     * @return     The result of the movement.
     */
    [[nodiscard]] static Point2D<T>
    operator+(const Direction2D& direction, const Point2D<T>& origin)
    {
        // TODO
    }
    /**
     * @brief      Converts the direction to an unitary @ref Vector2D object.
     *
     * @return     Vector2D representation of the direction.
     */
    [[nodiscard]] static Vector2D<T> toVector2D(const Direction2D& direction) const
    {
        T coordX = 0;
        T coordY = 0;
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

} // namespace utils::geometry2d