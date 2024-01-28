#include "Card.hpp"

#include <cmath>
#include <range/v3/algorithm/count_if.hpp>

namespace aoc_2023_4 {

uint32_t Card::calculatePoints() const
{
    auto winningCount{ranges::count_if(
        winningNumbers,
        [&candidates = std::as_const(candidateNumbers)](
            uint8_t const winningNumber) -> bool {
            return candidates.contains(winningNumber);
        })};
    return winningCount == 0U
        ? 0UL
        : static_cast<uint32_t>(std::pow(2U, winningCount - 1));
}

Card::Card(std::set<uint8_t>&& winnings, std::set<uint8_t>&& candidates)
    : winningNumbers{std::move(winnings)}
    , candidateNumbers{std::move(candidates)}
{
}

} // namespace aoc_2023_4
