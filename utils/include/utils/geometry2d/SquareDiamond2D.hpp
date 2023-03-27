#pragma once

#include "IShape2D.hpp"
#include "Point2D.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace utils::geometry2d {

class SquareDiamond2D : public IShape2D {
public:
    static constexpr uint32_t NumberOfVertexes{ 4U };

    SquareDiamond2D(const Point2D& centerPoint, const Point2D& perimeterPoint);
    SquareDiamond2D(const Point2D& centerPoint, uint32_t distance);
    const Point2D& getCenter() const;
    std::vector<Point2D> getVertexes() const override;
    uint32_t getDistance() const;
    std::optional<Point2D> stepAroundPerimeter() const noexcept;
    bool isOutside(const Point2D& point) const override;
    bool isInside(const Point2D& point) const override;
    bool isInPerimeter(const Point2D& point) const override;
    uint32_t area() const override;

private:
    const Point2D mCenter;
    const uint32_t mDistance;
    std::array<Point2D, NumberOfVertexes> mVertexes;
    std::optional<Point2D> mLastPerimeterPosition{};
};

} // namespace utils::geometry2d
