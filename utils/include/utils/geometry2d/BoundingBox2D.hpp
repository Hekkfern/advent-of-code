#pragma once

#include <cstdint>
#include <limits>

namespace utils::geometry2d {

class Point2D;
class Direction2D;

class BoundingBox2D {
public:
    void update(const Point2D& point2D);
    int32_t getMinX() const;
    int32_t getMaxX() const;
    int32_t getMinY() const;
    int32_t getMaxY() const;
    bool isOutside(const Point2D& point2D) const;
    bool isOutside(const Point2D& point2D, const Direction2D direction2D) const;

private:
    int32_t mMinX{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxX{ std::numeric_limits<int32_t>::min() };
    int32_t mMinY{ std::numeric_limits<int32_t>::max() };
    int32_t mMaxY{ std::numeric_limits<int32_t>::min() };
};

} // namespace utils::geometry2d
