#pragma once

#include <cstdint>
#include <utility>

namespace aoc_2022_9 {

enum class Direction;
class Vector2D;

class Position2D {
public:
    void move(Direction direction);
    void move(const Vector2D& vector);
    std::pair<int32_t, int32_t> get() const;
    int32_t getX() const;
    int32_t getY() const;

private:
    /**
     * Friend relationship of the equality operator overload.
     */
    friend bool operator==(const Position2D& lhs, const Position2D& rhs);

    int32_t mX = 0U;
    int32_t mY = 0U;
};

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the equality.
 */
bool operator==(const Position2D& lhs, const Position2D& rhs);

/**
 * @brief      Inequality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the inequality.
 */
bool operator!=(const Position2D& lhs, const Position2D& rhs);

} // namespace aoc_2022_9
