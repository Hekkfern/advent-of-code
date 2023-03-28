#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <utils/geometry2d/Direction2D.hpp>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2022_9 {

using namespace utils::geometry2d;

template <uint32_t RopeLength> class Rope {
public:
    void moveHead(Direction2D direction)
    {
        mKnots.front().move(direction);
        updateTails();
    }
    const Point2D& getTailPosition() const { return mKnots.back(); }

private:
    void updateTails()
    {
        for (size_t i = 1U; i < mKnots.size(); ++i) {
            const Vector2D vector2D{ mKnots.at(i), mKnots.at(i - 1U) };
            if (vector2D.range() <= 1U) {
                return;
            }

            const auto desiredMovement = vector2D.getCoordinates();
            const Vector2D movement{ std::clamp(desiredMovement.first, -1, 1),
                                     std::clamp(
                                         desiredMovement.second, -1, 1) };

            mKnots.at(i).move(movement);
        }
    }

    std::array<Point2D, RopeLength> mKnots{};
};

} // namespace aoc_2022_9
