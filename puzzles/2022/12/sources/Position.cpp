#include "Position.hpp"

namespace aoc_2022_12 {

Position::Position(
    Point2D<int32_t>&& pos, const Height height, const PositionType type)
    : mPoint2D{std::move(pos)}
    , mType{type}
    , mHeight{height}
{
}

std::pair<size_t, size_t> Position::getCoordinates() const
{
    return std::make_pair(
        static_cast<size_t>(mPoint2D.getX()),
        static_cast<size_t>(mPoint2D.getY()));
}

Height Position::getHeight() const { return mHeight; }

PositionType Position::getType() const { return mType; }

bool Position::operator==(Position const& other) const
{
    return mPoint2D == other.mPoint2D && mHeight == other.mHeight
        && mType == other.mType;
}

Point2D<int32_t> const& Position::getPoint() const { return mPoint2D; }

} // namespace aoc_2022_12
