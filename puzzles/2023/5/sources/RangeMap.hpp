#pragma once

#include "RangeMapSection.hpp"
#include <cstdint>
#include <vector>

namespace aoc_2023_5 {

class RangeMap {
public:
    RangeMap() = default;
    [[nodiscard]] uint64_t get(uint64_t key) const noexcept;
    void addSection(uint64_t dest, uint64_t src, uint64_t length) noexcept;

private:
    std::vector<RangeMapSection> mSections{};
};

} // namespace aoc_2023_5
