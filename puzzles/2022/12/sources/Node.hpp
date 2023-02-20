#pragma once

#include "Types.hpp"
#include <utils/geometry2d/Point2D.hpp>

namespace utils::geometry2D {
enum class Direction;
} // namespace utils::geometry2D

namespace aoc_2022_12 {

using namespace utils::geometry2d;

class Node {
public:
    Node(Point2D&& pos, Height height, bool isStartingPoint = false);
    const Point2D& getPosition() const;
    Height getHeight() const;
    bool isStartingPoint() const;

private:
    /**
     * Friend relationship of the equality operator overload.
     */
    friend bool operator==(const Node& lhs, const Node& rhs);
    /**
     * Friend relationship of the "greater than" operator overload.
     */
    friend bool operator>(const Node& lhs, const Node& rhs);

    const Point2D mPosition2D;
    const bool mIsStartingPoint = false;
    const Height mHeight;
};

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the equality.
 */
bool operator==(const Node& lhs, const Node& rhs);

/**
 * @brief      Inequality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the inequality.
 */
bool operator!=(const Node& lhs, const Node& rhs);

/**
 * @brief      "Greater than" operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the comparison.
 */
bool operator>(const Node& lhs, const Node& rhs);

/**
 * @brief      "Less than" operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the comparison.
 */
bool operator<(const Node& lhs, const Node& rhs);

} // namespace aoc_2022_12
