#pragma once

#include "Spring.hpp"
#include <vector>

namespace aoc_2023_12 {

class Record {
public:
    Record(
        std::vector<Spring>&& springs, std::vector<int>&& contiguosGroupInfo);
    /**
     * @brief
     *
     * @return Number of possible solutions.
     */
    u_int64_t solve();

private:
    std::vector<Spring>&& mSprings;
    std::vector<int> mContiguousGroupInfo;
};

} // namespace aoc_2023_12
