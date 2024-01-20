#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2023_2 {

using GameId = uint32_t;

struct GameRound {
    uint32_t numGreenBalls{0U};
    uint32_t numRedBalls{0U};
    uint32_t numBlueBalls{0U};
};

struct Game {
    GameId gameId{0U};
    std::vector<GameRound> rounds{};
};

} // namespace aoc_2023_2
