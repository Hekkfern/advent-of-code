#pragma once

#include "PositionType.hpp"
#include "Types.hpp"
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace utils::geometry2D {
enum class Direction;
} // namespace utils::geometry2D

namespace aoc_2022_12 {

using namespace utils::geometry2d;

class Position {
public:
    Position(Point2D<int32_t>&& pos, Height height, PositionType type);
    std::pair<size_t, size_t> getCoordinates() const;
    const Point2D<int32_t>& getPoint() const;
    Height getHeight() const;
    PositionType getType() const;
    bool operator==(const Position& other) const;

private:
    const Point2D<int32_t> mPoint2D;
    const PositionType mType;
    const Height mHeight;
};

Position operator+(const Position& position, const Direction2D& direction2D);

Position operator+(const Direction2D& direction2D, const Position& position);

} // namespace aoc_2022_12

template <>
struct std::hash<aoc_2022_12::Position> {
    std::size_t operator()(const aoc_2022_12::Position& k) const
    {
        return std::hash<utils::geometry2d::Point2D<int32_t>>()(k.getPoint());
    }
};
