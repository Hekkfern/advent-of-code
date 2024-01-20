#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2023_2 {

constexpr uint32_t MaxNumGreenBalls{12U};
constexpr uint32_t MaxNumRedBalls{13U};
constexpr uint32_t MaxNumBlueBalls{14U};

struct GameRound {
    uint32_t numGreenBalls;
    uint32_t numRedBalls;
    uint32_t numBlueBalls;

    [[nodiscard]] bool isPossible() const noexcept
    {
        return numGreenBalls <= MaxNumGreenBalls && numRedBalls < MaxNumRedBalls
            && numBlueBalls <= MaxNumBlueBalls;
    }
};

struct Game {
    uint32_t gameId;
    std::vector<GameRound> rounds;
};

} // namespace aoc_2023_2
