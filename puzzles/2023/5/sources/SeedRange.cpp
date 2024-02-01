#include "SeedRange.hpp"

namespace aoc_2023_5 {

SeedRange::SeedRange(uint64_t start, uint64_t size)
    : mStart{start}
    , mSize{size}
{
}

bool SeedRange::operator<(SeedRange const& other) const
{
    return mStart < other.mStart;
}

} // namespace aoc_2023_5
