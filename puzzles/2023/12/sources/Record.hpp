#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace aoc_2023_12 {

class Record {
public:
    Record(std::string&& springs, std::vector<int>&& contiguousGroupInfo);
    /**
     * @brief
     *
     * @return Number of possible solutions.
     */
    [[nodiscard]] uint64_t solve() const;

private:
    std::string mSprings;
    std::vector<int32_t> mContiguousGroupInfo;
};

} // namespace aoc_2023_12