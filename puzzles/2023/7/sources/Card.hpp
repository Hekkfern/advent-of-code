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

    // Make it comparable
    auto operator<=>(Card const& other) const = default;

    friend std::istream& operator>>(std::istream& s, Card& card)
    {
        while (std::isspace(s.peek()))
            s.ignore();
        switch (s.get()) {
        case '2':
            card.value = Two;
            break;
        case '3':
            card.value = Three;
            break;
        case '4':
            card.value = Four;
            break;
        case '5':
            card.value = Five;
            break;
        case '6':
            card.value = Six;
            break;
        case '7':
            card.value = Seven;
            break;
        case '8':
            card.value = Eight;
            break;
        case '9':
            card.value = Nine;
            break;
        case 'T':
            card.value = Ten;
            break;
        case 'J':
            card.value = Jack;
            break;
        case 'Q':
            card.value = Queen;
            break;
        case 'K':
            card.value = King;
            break;
        case 'A':
            card.value = Ace;
            break;
        default:
            s.setstate(std::ios_base::failbit);
            return s;
        }
        return s;
    }
};

} // namespace aoc_2023_7
