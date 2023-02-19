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
    bool canMove(const Direction direction);

private:
    const Point2D mPosition2D;
    const bool mIsStartingPoint = false;
    const Height mHeight;
};

} // namespace aoc_2022_12
