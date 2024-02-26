#pragma once

#include <compare>

namespace aoc_2023_7 {

struct Card2 {
    enum Type {
        Joker,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Queen,
        King,
        Ace
    } value;

    Card2() = default;

    explicit Card2(Type v)
        : value{v}
    {
    }

    [[nodiscard]] auto operator<=>(Card2 const& other) const = default;
};

} // namespace aoc_2023_7
