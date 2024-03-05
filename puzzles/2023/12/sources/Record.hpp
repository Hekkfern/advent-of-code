#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace aoc_2023_12 {

class Record {
public:
    Record(std::string&& springs, std::vector<int>&& contiguousGroupInfo);
    /**
     * @brief
     *
     * @return Number of possible solutions.
     */
    uint64_t solve();

private:
    std::string mSprings;
    std::vector<int32_t> mContiguousGroupInfo;
};

} // namespace aoc_2023_12
