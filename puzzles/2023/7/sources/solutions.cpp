#include "solutions.hpp"

#include "Card.hpp"
#include "Card2.hpp"
#include "Hand.hpp"
#include "Hand2.hpp"
#include <cassert>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/enumerate.hpp>
#include <sstream>
#include <utils/File.hpp>

namespace aoc_2023_7 {

// ---------- Private Methods ----------

Card parseCardForPart1(char const letter)
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

Hand parseHandForPart1(std::string_view const line)
{
    std::stringstream ss{std::string{line}};
    std::string cardsStr;
    uint32_t bid;
    ss >> cardsStr >> bid;
    std::array<Card, 5> cards{};
    for (auto const [i, c] : cardsStr | ranges::views::enumerate) {
        cards[i] = parseCardForPart1(c);
    }
    return Hand{cards, bid};
}

std::vector<Hand> parseInputForPart1(std::filesystem::path const& filePath)
{
    std::vector<Hand> handList;
    bool const result{utils::file::parseAndIterate(
        filePath, [&handList](std::string_view line) {
            handList.emplace_back(parseHandForPart1(line));
        })};
    if (!result) {
        return {};
    }

    return handList;
}

Card2 parseCardForPart2(char const letter)
{
    switch (letter) {
    case 'J':
        return Card2{Card2::Type::Joker};
    case '2':
        return Card2{Card2::Type::Two};
    case '3':
        return Card2{Card2::Type::Three};
    case '4':
        return Card2{Card2::Type::Four};
    case '5':
        return Card2{Card2::Type::Five};
    case '6':
        return Card2{Card2::Type::Six};
    case '7':
        return Card2{Card2::Type::Seven};
    case '8':
        return Card2{Card2::Type::Eight};
    case '9':
        return Card2{Card2::Type::Nine};
    case 'T':
        return Card2{Card2::Type::Ten};
    case 'Q':
        return Card2{Card2::Type::Queen};
    case 'K':
        return Card2{Card2::Type::King};
    case 'A':
        return Card2{Card2::Type::Ace};
    default:
        assert("Wrong card letter");
        return {};
    }
}

Hand2 parseHandForPart2(std::string_view const line)
{
    std::stringstream ss{std::string{line}};
    std::string cardsStr;
    uint32_t bid;
    ss >> cardsStr >> bid;
    std::array<Card2, 5> cards{};
    for (auto const [i, c] : cardsStr | ranges::views::enumerate) {
        cards[i] = parseCardForPart2(c);
    }
    return Hand2{cards, bid};
}

std::vector<Hand2> parseInputForPart2(std::filesystem::path const& filePath)
{
    std::vector<Hand2> handList;
    bool const result{utils::file::parseAndIterate(
        filePath, [&handList](std::string_view line) {
            handList.emplace_back(parseHandForPart2(line));
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
    auto hands{parseInputForPart1(filePath)};
    ranges::sort(hands, std::less{});
    uint64_t const result{ranges::accumulate(
        hands | ranges::views::enumerate,
        0ULL,
        [](uint64_t const accum, std::pair<uint64_t, Hand> item) -> uint64_t {
            return accum + ((item.first + 1ULL) * item.second.bid);
        })};
    return std::to_string(result);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto hands{parseInputForPart2(filePath)};
    ranges::sort(hands, std::less{});
    uint64_t const result{ranges::accumulate(
        hands | ranges::views::enumerate,
        0ULL,
        [](uint64_t const accum, std::pair<uint64_t, Hand2> item) -> uint64_t {
            return accum + ((item.first + 1ULL) * item.second.bid);
        })};
    return std::to_string(result);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_7