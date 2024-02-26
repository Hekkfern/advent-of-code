#include "solutions.hpp"

#include "Card.hpp"
#include "Hand.hpp"
#include <cassert>
#include <range/v3/view/enumerate.hpp>
#include <sstream>
#include <utils/File.hpp>

namespace aoc_2023_7 {

// ---------- Private Methods ----------

Card parseCard(char const letter)
{
    switch (letter) {
    case '2':
        return Card{Card::Type::Two};
    case '3':
        return Card{Card::Type::Three};
    case '4':
        return Card{Card::Type::Four};
    case '5':
        return Card{Card::Type::Five};
    case '6':
        return Card{Card::Type::Six};
    case '7':
        return Card{Card::Type::Seven};
    case '8':
        return Card{Card::Type::Eight};
    case '9':
        return Card{Card::Type::Nine};
    case 'T':
        return Card{Card::Type::Ten};
    case 'J':
        return Card{Card::Type::Jack};
    case 'Q':
        return Card{Card::Type::Queen};
    case 'K':
        return Card{Card::Type::King};
    case 'A':
        return Card{Card::Type::Ace};
    default:
        assert("Wrong card letter");
        return {};
    }
}

Hand parseHand(std::string_view const line)
{
    std::stringstream ss{std::string{line}};
    std::string cardsStr;
    uint32_t bid;
    ss >> cardsStr >> bid;
    std::array<Card, 5> cards{};
    for (auto const [i, c] : cardsStr | ranges::views::enumerate) {
        cards[i] = parseCard(c);
    }
    return Hand{cards, bid};
}

std::vector<Hand> parseInput(std::filesystem::path const& filePath)
{
    std::vector<Hand> handList;
    bool const result{utils::file::parseAndIterate(
        filePath, [&handList](std::string_view line) {
            handList.emplace_back(parseHand(line));
        })};
    if (!result) {
        return {};
    }

    return handList;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const input{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_7