#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace aoc_2023_5 {

class RangeMapSection {
public:
    RangeMapSection(uint64_t dest, uint64_t src, uint64_t length);
    [[nodiscard]] std::optional<uint64_t> get(uint64_t key) const noexcept;

private:
    uint64_t mDestinationStart;
    uint64_t mSourceStart;
    uint64_t mRangeLength;
};

class RangeMap {
public:
    RangeMap() = default;
    [[nodiscard]] uint64_t get(uint64_t key) const noexcept;
    void addSection(uint64_t dest, uint64_t src, uint64_t length) noexcept;

private:
    std::vector<RangeMapSection> mSections{};
};

} // namespace aoc_2023_5
