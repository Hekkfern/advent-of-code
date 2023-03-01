#pragma once

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <array>
#include <cstdint>

namespace utils::geometry2d {

class Rectangle2D {
public:
    static constexpr uint32_t NumberOfPoints{ 4U };
    static constexpr uint32_t NumberOfEdges{ NumberOfPoints };
    Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight);
    explicit Rectangle2D(
        const utils::geometry2d::Point2D& bottomLeft,
        const Vector2D& diagonal);
    Rectangle2D(const Point2D& bottomLeft, size_t width, size_t height);
    std::pair<size_t, size_t> size() const;
    uint32_t area() const;
    bool isOutside(const Point2D& other) const;
    bool isInside(const Point2D& other) const;
    bool isInPerimeter(const Point2D& other) const;

private:
    const Point2D& getBottomLeftPoint() const;
    const Point2D& getTopRightPoint() const;

    const std::array<Point2D, NumberOfPoints> mPoints;
    const size_t mWidth;
    const size_t mHeight;
};

} // namespace utils::geometry2d
