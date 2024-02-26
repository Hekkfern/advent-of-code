#pragma once

#include <istream>

namespace aoc_2023_7 {

struct Card {
    enum Type {
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    } value;

    Card() = default;

    explicit Card(Type v)
        : value{v}
    {
    }

    [[nodiscard]] auto operator<=>(Card const& other) const = default;
};

} // namespace aoc_2023_7
