#include "Card.hpp"

#include <cmath>
#include <range/v3/algorithm/count_if.hpp>

namespace aoc_2023_4 {

uint32_t Card::calculatePoints() const noexcept
{
    auto winningCount{calculateMatchingNumbers()};
    return winningCount == 0UL
        ? 0UL
        : static_cast<uint32_t>(std::pow(2U, winningCount - 1));
}

Card::Card(
    CardId id, std::set<uint8_t>&& winnings, std::set<uint8_t>&& candidates)
    : cardId{id}
    , winningNumbers{std::move(winnings)}
    , candidateNumbers{std::move(candidates)}
{
}

uint32_t Card::calculateMatchingNumbers() const noexcept
{
    return ranges::count_if(
        winningNumbers,
        [&candidates = std::as_const(candidateNumbers)](
            uint8_t const winningNumber) -> bool {
            return candidates.contains(winningNumber);
        });
}

bool Card::operator==(Card const& other) const
{
    return cardId == other.cardId && winningNumbers == other.winningNumbers
        && candidateNumbers == other.candidateNumbers;
}

} // namespace aoc_2023_4
