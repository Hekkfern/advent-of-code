#pragma once

#include "Card.hpp"
#include <algorithm>
#include <array>
#include <cstdint>

namespace aoc_2023_7 {

class Hand {
public:
    enum Type {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfKind,
        FullHouse,
        FourOfKind,
        FiveOfKind
    } value;

    std::array<Card, 5> cards;
    uint32_t bid;

    friend std::istream& operator>>(std::istream& s, Hand& hand)
    {
        for (auto& e : hand.cards) {
            if (!(s >> e)) {
                return s;
            }
        }
        if (!(s >> hand.bid)) {
            return s;
        }
        hand.analyzeHand();
        return s;
    }

    auto operator<=>(Hand const& other) const
    {
        // First compare by the hand value
        auto cmp = value <=> other.value;
        if (std::is_neq(cmp))
            return cmp;
        // If the hands are the same, lexicographically compare the cards
        return cards <=> other.cards;
    }

private:
    void analyzeHand()
    {
        std::array<Card, 5> sorted_cards{cards};
        std::ranges::sort(sorted_cards, std::greater<>{});

        // Translate cards into frequencies of equal cards
        std::array<uint32_t, 5ULL> freq{1U, 0U, 0U, 0U, 0U};
        auto it = freq.begin();
        for (std::size_t i = 1ULL; i < 5ULL; ++i) {
            if (sorted_cards[i - 1ULL] != sorted_cards[i]) {
                ++it;
            }
            ++*it;
        }
        std::ranges::sort(freq, std::greater<>{});
        // Map the frequencies to the hand value
        if (freq[0] == 5U) {
            value = FiveOfKind;
        } else if (freq[0] == 4U) {
            value = FourOfKind;
        } else if (freq[0] == 3U && freq[1] == 2U) {
            value = FullHouse;
        } else if (freq[0] == 3U && freq[1] != 2U) {
            value = ThreeOfKind;
        } else if (freq[0] == 2U && freq[1] == 2U) {
            value = TwoPair;
        } else if (freq[0] == 2U && freq[1] != 2U) {
            value = OnePair;
        } else {
            value = HighCard;
        }
    }
};

} // namespace aoc_2023_7
