#pragma once

#include "Point2D.hpp"
#include <vector>

namespace utils::geometry2d {

class IShape2D {
public:
    virtual ~IShape2D() = default;
    virtual std::vector<Point2D> getVertexes() const = 0;
    virtual uint32_t area() const = 0;
    virtual bool isOutside(const Point2D& point) const = 0;
    virtual bool isInside(const Point2D& point) const = 0;
    virtual bool isInPerimeter(const Point2D& point) const = 0;
};

} // namespace utils::geometry2d
