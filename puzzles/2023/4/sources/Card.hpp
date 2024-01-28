#pragma once

#include <cstdint>
#include <set>

namespace aoc_2023_4 {

using CardId = uint8_t;

struct Card {
    CardId cardId;
    std::set<uint8_t> winningNumbers;
    std::set<uint8_t> candidateNumbers;

    Card(
        CardId id,
        std::set<uint8_t>&& winnings,
        std::set<uint8_t>&& candidates);

    [[nodiscard]] uint32_t calculatePoints() const;
};

} // namespace aoc_2023_4
