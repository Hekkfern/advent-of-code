#pragma once

#include <cstdint>
#include <limits>

namespace utils::geometry2d {

class Point2D;

class BoundingBox2D {
public:
    void update(int32_t x, int32_t y);
    void update(const Point2D& point2D);
    int32_t getMinX() const;
    int32_t getMaxX() const;
    int32_t getMinY() const;
    int32_t getMaxY() const;

private:
    int32_t mMinX{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxX{ std::numeric_limits<int32_t>::min() };
    int32_t mMinY{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxY{ std::numeric_limits<int32_t>::min() };
};

} // namespace utils::geometry2d
