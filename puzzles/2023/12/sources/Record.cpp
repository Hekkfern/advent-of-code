#include "Record.hpp"

#include <range/v3/algorithm/for_each.hpp>

namespace {
enum class ExpandedSpringStatus { OneDamaged, GroupOfOperational };

/**
 * \brief
 *
 * \param groupInfo
 *
 * \return List. Both extremes are guaranteed to be @ref
 * ExpandedSpringStatus::GroupOfOperational.
 */
std::vector<ExpandedSpringStatus>
expandContiguousGroupInfo(std::vector<int32_t> const& groupInfo)
{
    std::vector<ExpandedSpringStatus> result{
        ExpandedSpringStatus::GroupOfOperational};
    ranges::for_each(groupInfo, [&result](int32_t const value) -> void {
        for (int32_t i{0}; i < value; ++i) {
            result.emplace_back(ExpandedSpringStatus::OneDamaged);
        }
        result.emplace_back(ExpandedSpringStatus::GroupOfOperational);
    });
    return result;
}
} // namespace

namespace aoc_2023_12 {

Record::Record(std::string&& springs, std::vector<int>&& contiguousGroupInfo)
    : mSprings{std::move(springs)}
    , mContiguousGroupInfo{std::move(contiguousGroupInfo)}
{
}

uint32_t Record::solve() const
{
    // add extra operational springs in both sides
    std::string springsStr{mSprings};
    springsStr.insert(0, ".");
    springsStr += '.';

    // translate groupInfo
    auto const expandedGroupInfo{
        expandContiguousGroupInfo(mContiguousGroupInfo)};

    // solve
    int32_t const n{static_cast<int32_t>(springsStr.size())};
    int32_t const m{static_cast<int32_t>(expandedGroupInfo.size())};
    std::vector<std::vector<uint32_t>> dp(
        n + 1, std::vector<uint32_t>(m + 1, 0));
    dp[n][m] = 1;

    for (int32_t i = n - 1; i >= 0; --i) {
        for (int32_t j = m - 1; j >= std::max(m - (n - i), 0); --j) {
            bool damaged = false;
            bool operational = false;
            switch (springsStr[i]) {
            case '#': {
                damaged = true;
                break;
            }
            case '.': {
                operational = true;
                break;
            }
            default: {
                operational = true;
                damaged = true;
                break;
            }
            }
            uint32_t sum{0};
            if (damaged
                && expandedGroupInfo[j] == ExpandedSpringStatus::OneDamaged) {
                sum += dp[i + 1][j + 1];
            } else if (
                operational
                && expandedGroupInfo[j]
                    == ExpandedSpringStatus::GroupOfOperational) {
                sum += dp[i + 1][j + 1] + dp[i + 1][j];
            }
            dp[i][j] = sum;
        }
    }
    return dp[0][0];
}

} // namespace aoc_2023_12
