#pragma once

#include <array>
#include <cstdint>
#include <utils/geometry2d/Position2D.h>
#include <utils/geometry2d/Vector2D.h>

namespace aoc_2022_9 {

template <uint32_t RopeLength> class Rope {
public:
    void moveHead(Direction direction)
    {
        mKnots.front().move(direction);
        updateTails();
    }
    const Position2D& getTailPosition() const { return mKnots.back(); }

private:
    void updateTails()
    {
        for (size_t i = 1U; i < mKnots.size(); ++i) {
            const Vector2D vector2D{ mKnots.at(i), mKnots.at(i - 1U) };
            if (vector2D.distance() <= 1U) {
                return;
            }

            const auto desiredMovement = vector2D.get();
            const Vector2D movement{ std::clamp(desiredMovement.first, -1, 1),
                                     std::clamp(
                                         desiredMovement.second, -1, 1) };

            mKnots.at(i).move(movement);
        }
    }

    std::array<Position2D, RopeLength> mKnots{};
};

} // namespace aoc_2022_9
