#pragma once

#include <utils/interval/Interval.hpp>

namespace aoc_2023_19::part2 {

struct PartRange {
    PartRange() = default;

    [[nodiscard]] uint64_t calculateNumberOfCombinations() const noexcept;

    utils::interval::Interval<> x{1, 4000};
    utils::interval::Interval<> m{1, 4000};
    utils::interval::Interval<> a{1, 4000};
    utils::interval::Interval<> s{1, 4000};
};

} // namespace aoc_2023_19
