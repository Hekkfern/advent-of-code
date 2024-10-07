#include "PartRange.h"

namespace aoc_2023_19::part2 {

[[nodiscard]] uint64_t PartRange::calculateNumberOfCombinations() const noexcept
{
    return x.size() * m.size() * a.size() * s.size();
}

} // namespace aoc_2023_19::part2
