#include "solutions.hpp"

#include "Card.hpp"
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_4 {

// ---------- Private Methods ----------

std::set<uint8_t> parseNumbers(std::string_view const numbersStr)
{
    static constexpr auto SpaceSeparator{" "};

    auto numbersStrList{utils::string::split(numbersStr, SpaceSeparator)};
    return numbersStrList
        | ranges::views::transform([](std::string const& str) -> uint8_t {
               return *utils::string::toNumber<uint8_t>(str);
           })
        | ranges::to<std::set>;
}

Card parseInputLine(std::string_view line) noexcept
{
    static constexpr auto CardSeparator{":"};
    static constexpr auto TypeSeparator{"|"};

    auto cardData{utils::string::split(line, CardSeparator)};
    Card::CardId cardId{*utils::string::toNumber<
        Card::CardId>(utils::string::split(
        utils::string::remove_excess_whitespace(cardData[0]))[1])};
    auto numbers{utils::string::split(
        utils::string::remove_excess_whitespace(
            utils::string::trim(cardData[1])),
        TypeSeparator)};
    auto winningNumbers{parseNumbers(numbers[0])};
    auto candidateNumbers{parseNumbers(numbers[1])};

    return Card{cardId, std::move(winningNumbers), std::move(candidateNumbers)};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t accumPoints{0UL};
    utils::file::parseAndIterate(
        filePath, [&accumPoints](std::string_view const line) -> void {
            auto card{parseInputLine(line)};
            accumPoints += card.calculatePoints();
        });
    return std::to_string(accumPoints);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    std::unordered_map<Card::CardId, uint32_t> copies;
    utils::file::parseAndIterate(
        filePath, [&copies](std::string_view const line) -> void {
            auto card{parseInputLine(line)};
            // create new card
            copies[card.cardId] += 1UL;
            // increase number of copies
            auto numMatchingNumbers{card.calculateMatchingNumbers()};
            if (numMatchingNumbers > 0UL) {
                for (const auto index :
                     ranges::views::iota(1UL, numMatchingNumbers)) {
                    copies[card.cardId + static_cast<Card::CardId>(index)]
                        += 1UL;
                }
            }
        });

    return std::to_string(ranges::fold_left(
        copies,
        0UL,
        [](uint32_t accum, std::pair<Card::CardId, uint32_t> const& card)
            -> uint32_t { return accum + card.second; }));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_4