#pragma once

#include <cstdint>
#include <utility>

namespace aoc_2022_9 {

class Position2D;

class Vector2D {
public:
    Vector2D(int32_t x, int32_t y);
    Vector2D(const Position2D& origin, const Position2D& destination);
    std::pair<int32_t, int32_t> get() const;
    int32_t getX() const;
    int32_t getY() const;
    uint32_t distance() const;

private:
    int32_t mX;
    int32_t mY;
};

} // namespace aoc_2022_9
