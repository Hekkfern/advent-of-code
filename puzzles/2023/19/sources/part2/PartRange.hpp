#pragma once

#include <utils/interval/Interval.hpp>

namespace aoc_2023_19::part2 {

using Range = utils::interval::Interval<>;

struct PartRange {
    PartRange() = default;

    [[nodiscard]] uint64_t calculateNumberOfCombinations() const noexcept;

    Range x{1, 4000};
    Range m{1, 4000};
    Range a{1, 4000};
    Range s{1, 4000};
};

} // namespace aoc_2023_19::part2
