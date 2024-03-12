#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace aoc_2023_12 {

class Record {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  springs              The springs
     * @param[in]  contiguousGroupInfo  The contiguous group information
     */
    Record(std::string&& springs, std::vector<int>&& contiguousGroupInfo);
    /**
     * @brief      Calculates the number of permutations using the original
     *             record data.
     *
     * @return     Number of matching solutions.
     */
    [[nodiscard]] uint64_t solveOriginal() const;
    /**
     * @brief      Calculates the number of permutations using the record data
     *             which has been expanded up to 5 copies.
     *
     * @return     Number of matching solutions.
     */
    [[nodiscard]] uint64_t solveUnfolded() const;

private:
    std::string mSprings;
    std::vector<int32_t> mContiguousGroupInfo;
};

} // namespace aoc_2023_12
