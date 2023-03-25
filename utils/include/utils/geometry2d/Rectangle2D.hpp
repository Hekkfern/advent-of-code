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
    static constexpr uint32_t NumberOfEdges{ NumberOfVertexes };

    Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight);
    explicit Rectangle2D(
        const utils::geometry2d::Point2D& bottomLeft,
        const Vector2D& diagonal);
    Rectangle2D(const Point2D& bottomLeft, size_t width, size_t height);
    std::pair<size_t, size_t> size() const;
    uint32_t area() const override;
    bool isOutside(const Point2D& point) const override;
    bool isInside(const Point2D& point) const override;
    bool isInPerimeter(const Point2D& point) const override;
    std::vector<Point2D> getVertexes() const override;

private:
    const Point2D& getBottomLeftPoint() const;
    const Point2D& getTopRightPoint() const;

    const std::array<Point2D, NumberOfVertexes> mVertexes;
    const size_t mWidth;
    const size_t mHeight;
};

} // namespace utils::geometry2d
