#pragma once

#include <cstdint>
#include <optional>
#include <utils/interval/Interval.hpp>
#include <utils/interval/IntervalSet.hpp>

namespace aoc_2023_5 {

class RangeMapSection {
public:
    RangeMapSection() noexcept = default;
    RangeMapSection(int64_t dest, int64_t src, int64_t length) noexcept;
    [[nodiscard]] std::optional<int64_t> convert(int64_t key) const noexcept;
    [[nodiscard]] bool operator<(RangeMapSection const& other) const noexcept;
    [[nodiscard]] bool operator==(RangeMapSection const& other) const noexcept;
    [[nodiscard]] utils::interval::Interval<int64_t> const& getSource() const;

private:
    utils::interval::Interval<int64_t> mDestination;
    utils::interval::Interval<int64_t> mSource;
};

} // namespace aoc_2023_5
