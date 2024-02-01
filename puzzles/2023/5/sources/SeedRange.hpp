#pragma once

#include <cstdint>
namespace aoc_2023_5 {

class SeedRange {
public:
    SeedRange(uint64_t start, uint64_t size);
    bool operator<(SeedRange const& other) const;
private:
    uint64_t mStart;
    uint64_t mSize;
};

} // namespace aoc_2023_5
