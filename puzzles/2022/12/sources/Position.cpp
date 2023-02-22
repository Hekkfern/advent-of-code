#include "Position.hpp"

namespace aoc_2022_12 {

Position::Position(Point2D&& pos, const Height height, const PositionType type)
    : mPoint2D{ std::move(pos) }
    , mType{ type }
    , mHeight{ height }
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

bool Position::operator==(const Position& other) const
{
    return mHeight == other.mHeight;
}

bool Position::operator<(const Position& other) const
{
    return mHeight < other.mHeight;
}

bool Position::operator<=(const Position& other) const
{
    return (*this == other) || (*this < other);
}

const Point2D& Position::getPoint() const { return mPoint2D; }

} // namespace aoc_2022_12