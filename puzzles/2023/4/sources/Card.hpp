#pragma once

#include <cstdint>
#include <functional>
#include <set>

namespace aoc_2023_4 {

struct Card {
    using CardId = uint8_t;

    CardId cardId;
    std::set<uint8_t> winningNumbers;
    std::set<uint8_t> candidateNumbers;

    Card(
        CardId id,
        std::set<uint8_t>&& winnings,
        std::set<uint8_t>&& candidates);

    [[nodiscard]] uint32_t calculatePoints() const noexcept;

    uint32_t calculateMatchingNumbers() const noexcept;

    bool operator==(Card const& other) const;
};

} // namespace aoc_2023_4

template <>
struct std::hash<aoc_2023_4::Card> {
    std::size_t operator()(aoc_2023_4::Card const& k) const noexcept
    {
        return std::hash<aoc_2023_4::Card::CardId>()(k.cardId);
    }
};
