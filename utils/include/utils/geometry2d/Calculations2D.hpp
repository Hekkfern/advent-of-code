#pragma once

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "utils/Concepts.hpp"
#include <numbers>

namespace utils::geometry2d {

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
double
calculateArbitraryPolygonArea(std::vector<Point2D<T>> const& perimeterPoints)
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
    std::vector<Point2D<T>> const& perimeterPoints)
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
