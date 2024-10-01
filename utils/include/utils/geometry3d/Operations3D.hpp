#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "utils/Concepts.hpp"

namespace utils::geometry3d {

template <SignedIntegerType T = int32_t>
class Operations3D {
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
    [[nodiscard]] static Point3D<T>
    move(Point3D<T> const& origin, Vector3D<T> const& movement)
    {
        return Point3D<T>{
            origin.getX() + movement.getX(),
            origin.getY() + movement.getY(),
            origin.getZ() + movement.getZ()};
    }
};

/**
 * @brief      Addition operator to move a @ref Point3D according to a @ref
 * Vector3D.
 *
 * @param[in]  origin   Original position.
 * @param[in]  movement  Vector of movement.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point3D<T>
operator+(Point3D<T> const& origin, Vector3D<T> const& movement)
{
    return Operations3D<T>::move(origin, movement);
}
/**
 * @brief      Addition operator to move a @ref Point3D according to a @ref
 * Vector3D.
 *
 * @param[in]  movement  Vector of movement.
 * @param[in]  origin   Original position.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
[[nodiscard]] Point3D<T>
operator+(Vector3D<T> const& movement, Point3D<T> const& origin)
{
    return Operations3D<T>::move(origin, movement);
}
/**
 * @brief      Addition assignment operator to move a @ref Point3D according to
 *             a @ref Vector3D.
 *
 * @param[in]  point     Original position.
 * @param[in]  movement  Vector of movement.
 *
 * @tparam     T         Type of the coordinates.
 *
 * @return     The result of the movement.
 */
template <SignedIntegerType T = int32_t>
void operator+=(Point3D<T>& point, Vector3D<T> const& movement)
{
    point = point + movement;
}

} // namespace utils::geometry3d
