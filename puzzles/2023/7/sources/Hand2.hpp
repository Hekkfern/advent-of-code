#pragma once

#include "Card2.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/sort.hpp>

namespace aoc_2023_7 {

class Hand2 {
public:
    std::array<Card2, 5> cards;
    uint32_t bid;
    enum Type {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfKind,
        FullHouse,
        FourOfKind,
        FiveOfKind
    } value;

    Hand2(std::array<Card2, 5> const c, uint32_t const b)
        : cards{c}
        , bid{b}
        , value{analyzeHand(cards)}
    {
    }

    [[nodiscard]] auto operator<=>(Hand2 const& other) const
    {
        // First compare by the hand value
        auto cmp = value <=> other.value;
        if (std::is_neq(cmp)) {
            return cmp;
        }
        // If the hands are the same, lexicographically compare the cards
        return cards <=> other.cards;
    }

private:
    static Type analyzeHand(std::array<Card2, 5> c)
    {
        std::array<Card2, 5> sorted_cards{c};
        ranges::sort(sorted_cards, std::greater{});

        // Translate cards into frequencies of equal cards
        std::array<uint32_t, 5ULL> freq{1U, 0U, 0U, 0U, 0U};
        auto it{freq.begin()};
        uint32_t numJokers{0U};
        for (std::size_t i{1ULL}; i < 5ULL; ++i) {
            if (sorted_cards[i].value == Card2::Type::Joker) {
                ++numJokers;
            } else {
                if (sorted_cards[i - 1ULL] != sorted_cards[i]) {
                    ++it;
                }
                ++*it;
            }
        }
        ranges::sort(freq, std::greater{});
        freq[0] += numJokers;
        // Map the frequencies to the hand value
        if (freq[0] >= 5U) {
            return FiveOfKind;
        } else if (freq[0] == 4U) {
            return FourOfKind;
        } else if (freq[0] == 3U && freq[1] == 2U) {
            return FullHouse;
        } else if (freq[0] == 3U && freq[1] != 2U) {
            return ThreeOfKind;
        } else if (freq[0] == 2U && freq[1] == 2U) {
            return TwoPair;
        } else if (freq[0] == 2U && freq[1] != 2U) {
            return OnePair;
        } else {
            return HighCard;
        }
    }
};

} // namespace aoc_2023_7
