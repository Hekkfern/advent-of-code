#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "utils/Concepts.hpp"
#include "utils/Math.hpp"

namespace utils::geometry3d {

/**
 * @brief      Calculates the point result of applying an arbitrary
 * movement to the selected point.
 *
 * @param[in]  origin      The origin point.
 * @param[in]  movement  The vector of the movement.
 *
 * @return     Resulting position of the movement.
 */
template <SignedIntegerType T = int32_t>
[[maybe_unused]] [[nodiscard]] static std::optional<Point3D<T>>
move(Point3D<T> const& origin, Vector3D<T> const& movement) noexcept
{
    if (utils::math::willAdditionOverflow(origin.getX(), movement.getX())) {
        return std::nullopt;
    }
    if (utils::math::willAdditionOverflow(origin.getY(), movement.getY())) {
        return std::nullopt;
    }
    if (utils::math::willAdditionOverflow(origin.getZ(), movement.getZ())) {
        return std::nullopt;
    }
    return Point3D<T>{
        origin.getX() + movement.getX(),
        origin.getY() + movement.getY(),
        origin.getZ() + movement.getZ()};
}

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
[[nodiscard]] std::optional<Point3D<T>>
operator+(Point3D<T> const& origin, Vector3D<T> const& movement) noexcept
{
    return move(origin, movement);
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
[[nodiscard]] std::optional<Point3D<T>>
operator+(Vector3D<T> const& movement, Point3D<T> const& origin) noexcept
{
    return move(origin, movement);
}

} // namespace utils::geometry3d
