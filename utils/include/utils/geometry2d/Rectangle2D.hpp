#pragma once

#include "IShape2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace utils::geometry2d {

class Rectangle2D : public IShape2D {
public:
    static constexpr uint32_t NumberOfVertexes{ 4U };

    Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight);
    explicit Rectangle2D(
        const utils::geometry2d::Point2D& bottomLeft,
        const Vector2D& diagonal);
    Rectangle2D(const Point2D& bottomLeft, uint32_t width, uint32_t height);
    std::pair<size_t, size_t> size() const;
    uint32_t area() const override;
    bool isOutside(const Point2D& point) const override;
    bool isInside(const Point2D& point) const override;
    bool isInPerimeter(const Point2D& point) const override;
    std::vector<Point2D> getVertexes() const override;
    uint32_t getWidth() const;
    uint32_t getHeight() const;

private:
    const Point2D& getBottomLeftPoint() const;
    const Point2D& getTopRightPoint() const;

    const std::array<Point2D, NumberOfVertexes> mVertexes;
    const uint32_t mWidth;
    const uint32_t mHeight;
};

} // namespace utils::geometry2d
