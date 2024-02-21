#pragma once

#include "RangeMapSection.hpp"
#include <cstdint>
#include <set>

namespace aoc_2023_5 {

class RangeMap {
public:
    RangeMap() = default;
    [[nodiscard]] int64_t convert(int64_t key) const noexcept;
    [[nodiscard]] utils::interval::IntervalSet<int64_t> convert(
        utils::interval::Interval<int64_t> const& keyInterval) const noexcept;
    void addSection(int64_t dest, int64_t src, int64_t length) noexcept;

private:
    std::set<RangeMapSection> mSections{};
};

} // namespace aoc_2023_5
