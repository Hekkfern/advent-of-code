#pragma once

#include <cstdint>
#include <optional>
#include <utils/interval/Interval.hpp>

namespace aoc_2023_5 {

class RangeMapSection {
public:
    RangeMapSection(int64_t dest, int64_t src, int64_t length);
    [[nodiscard]] std::optional<int64_t> get(int64_t key) const noexcept;
    bool operator<(RangeMapSection const& other) const;

private:
    utils::interval::Interval<int64_t> mDestination;
    utils::interval::Interval<int64_t> mSource;
};

} // namespace aoc_2023_5
