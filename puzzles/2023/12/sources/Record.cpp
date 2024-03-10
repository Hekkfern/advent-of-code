#include "Record.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/unique.hpp>

namespace {
enum class ExpandedSpringStatus { OneDamaged, GroupOfOperational };

template <typename T>
std::vector<T> removeConsecutiveDuplicates(std::vector<T> const& container)
{
    return container | ranges::views::unique | ranges::to<std::vector>;
}

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

uint32_t Record::solveOriginal() const
{
    // add extra operational springs in both sides
    std::string const extendedSprings{"." + mSprings + "."};

    // translate groupInfo
    auto const expandedGroupInfo{
        expandContiguousGroupInfo(mContiguousGroupInfo)};

    // solve
    int32_t const n{static_cast<int32_t>(extendedSprings.size())};
    int32_t const m{static_cast<int32_t>(expandedGroupInfo.size())};
    std::vector<std::vector<uint32_t>> dp(
        n + 1, std::vector<uint32_t>(m + 1, 0));
    dp[n][m] = 1;

    for (int32_t i = n - 1; i >= 0; --i) {
        for (int32_t j = m - 1; j >= std::max(m - (n - i), 0); --j) {
            uint32_t value{0};
            if (extendedSprings[i] != '.'
                && expandedGroupInfo[j] == ExpandedSpringStatus::OneDamaged) {
                value = dp[i + 1][j + 1];
            } else if (
                extendedSprings[i] != '#'
                && expandedGroupInfo[j]
                    == ExpandedSpringStatus::GroupOfOperational) {
                value = dp[i + 1][j + 1] + dp[i + 1][j];
            }
            dp[i][j] = value;
        }
    }
    return dp[0][0];
}

uint32_t Record::solveUnfolded() const
{
    // create 4 more copies and add extra operational springs in both sides
    std::string extendedSprings = ".";
    for (int i = 0; i < 5; ++i) {
        extendedSprings += mSprings + (i < 4 ? "?" : ".");
    }

    // translate groupInfo and create 4 more copies
    auto const expandedGroupInfo{
        expandContiguousGroupInfo(mContiguousGroupInfo)};
    auto extendedGroupInfo{expandedGroupInfo};
    for (int i = 0; i < 5; ++i) {
        extendedGroupInfo.insert(
            std::end(extendedGroupInfo),
            std::begin(expandedGroupInfo),
            std::end(expandedGroupInfo));
    }
    extendedGroupInfo = removeConsecutiveDuplicates(expandedGroupInfo);

    // solve
    int64_t const n{std::ssize(extendedSprings)};
    int64_t const m{std::ssize(extendedGroupInfo)};
    std::vector<std::vector<uint32_t>> dp(
        n + 1, std::vector<uint32_t>(m + 1, 0));
    dp[n][m] = 1;

    for (int64_t i = n - 1; i >= 0; --i) {
        for (int64_t j = m - 1; j >= std::max<int64_t>(m - (n - i), 0); --j) {
            uint32_t value{0};
            if (extendedSprings[i] != '.'
                && expandedGroupInfo[j] == ExpandedSpringStatus::OneDamaged) {
                value = dp[i + 1][j + 1];
            } else if (
                extendedSprings[i] != '#'
                && expandedGroupInfo[j]
                    == ExpandedSpringStatus::GroupOfOperational) {
                value = dp[i + 1][j + 1] + dp[i + 1][j];
            }
            dp[i][j] = value;
        }
    }
    return dp[0][0];
}

} // namespace aoc_2023_12
