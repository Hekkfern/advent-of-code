#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace aoc_2023_5 {

class RangeMapSection {
public:
    RangeMapSection(uint32_t dest, uint32_t src, uint32_t length);
    [[nodiscard]] std::optional<uint32_t> get(uint32_t key) const noexcept;

private:
    uint32_t mDestinationStart;
    uint32_t mSourceStart;
    uint32_t mRangeLength;
};

class RangeMap {
public:
    RangeMap() = default;
    [[nodiscard]] uint32_t get(uint32_t key) const noexcept;
    void addSection(uint32_t dest, uint32_t src, uint32_t length) noexcept;

private:
    std::vector<RangeMapSection> mSections{};
};

} // namespace aoc_2023_5
