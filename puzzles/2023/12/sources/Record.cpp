#include "Record.hpp"

namespace aoc_2023_12 {

Record::Record(
    std::vector<Spring>&& springs, std::vector<int>&& contiguousGroupInfo)
    : mSprings{std::move(springs)}
    , mContiguousGroupInfo{std::move(contiguousGroupInfo)}
{
}

} // namespace aoc_2023_12
