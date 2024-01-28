#pragma once

#include <cstdint>
#include <set>

namespace aoc_2023_4 {

struct Card {
    std::set<uint8_t> winningNumbers;
    std::set<uint8_t> candidateNumbers;

    Card(std::set<uint8_t>&& winnings, std::set<uint8_t>&& candidates);

    [[nodiscard]] uint32_t calculatePoints() const;
};

} // namespace aoc_2023_4
