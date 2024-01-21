#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <range/v3/all.hpp>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Operations2D.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2022_9 {

using namespace utils::geometry2d;

template <uint32_t RopeLength>
class Rope {
public:
    void moveHead(Direction2D direction)
    {
        mKnots.front() += direction;
        updateTails();
    }
    Point2D<int32_t> const& getTailPosition() const { return mKnots.back(); }

private:
    void updateTails()
    {
        for (auto [index, point] :
             mKnots | ranges::views::enumerate | ranges::views::drop(1)) {
            Vector2D const vector2D{point, mKnots.at(index - 1U)};
            if (vector2D.range() <= 1U) {
                return;
            }

            Coord2D<int32_t> const desiredMovement{vector2D.getCoordinates()};
            Vector2D<int32_t> const movement{
                std::clamp(desiredMovement.mX, -1, 1),
                std::clamp(desiredMovement.mY, -1, 1)};

            point += movement;
        }
    }

    std::array<Point2D<int32_t>, RopeLength> mKnots;
};

} // namespace aoc_2022_9
