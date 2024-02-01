#pragma once

#include <cstdint>
#include <optional>

namespace aoc_2023_5 {

class RangeMapSection {
public:
    RangeMapSection(uint64_t dest, uint64_t src, uint64_t length);
    [[nodiscard]] std::optional<uint64_t> get(uint64_t key) const noexcept;
    bool operator<(RangeMapSection const& other) const;

private:
    uint64_t mDestinationStart;
    uint64_t mSourceStart;
    uint64_t mRangeLength;
};

} // namespace aoc_2023_5