#pragma once

#include <cstdint>
#include <range/v3/algorithm/all_of.hpp>
#include <vector>

namespace {
constexpr uint32_t MaxNumGreenBalls{12U};
constexpr uint32_t MaxNumRedBalls{13U};
constexpr uint32_t MaxNumBlueBalls{14U};
} // namespace

namespace aoc_2023_2 {

using GameId = uint32_t;

struct GameRound {
    uint32_t numGreenBalls{0U};
    uint32_t numRedBalls{0U};
    uint32_t numBlueBalls{0U};

    [[nodiscard]] bool isPossible() const noexcept
    {
        return numGreenBalls <= MaxNumGreenBalls && numRedBalls < MaxNumRedBalls
            && numBlueBalls <= MaxNumBlueBalls;
    }
};

struct Game {
    GameId gameId{0U};
    std::vector<GameRound> rounds{};

    [[nodiscard]] bool isPossible() const noexcept
    {
        return ranges::all_of(rounds, [](GameRound const& item) -> bool {
            return item.isPossible();
        });
    }
};

} // namespace aoc_2023_2
