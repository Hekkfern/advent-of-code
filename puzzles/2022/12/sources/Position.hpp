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
    Point2D<int32_t> const& getPoint() const;
    Height getHeight() const;
    PositionType getType() const;
    bool operator==(Position const& other) const;

private:
    Point2D<int32_t> const mPoint2D;
    PositionType const mType;
    Height const mHeight;
};

Position operator+(Position const& position, Direction2D const& direction2D);

Position operator+(Direction2D const& direction2D, Position const& position);

} // namespace aoc_2022_12

template <>
struct std::hash<aoc_2022_12::Position> {
    std::size_t operator()(aoc_2022_12::Position const& k) const
    {
        return std::hash<utils::geometry2d::Point2D<int32_t>>()(k.getPoint());
    }
};
