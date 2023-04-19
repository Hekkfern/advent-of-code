#pragma once

#include "../Concepts.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

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
    move(const Point3D<T>& origin, const Vector3D<T>& movement)
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
operator+(const Point3D<T>& origin, const Vector3D<T>& movement)
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
operator+(const Vector3D<T>& movement, const Point3D<T>& origin)
{
    return Operations3D<T>::move(origin, movement);
}

} // namespace utils::geometry3d
