#include "Record.hpp"

#include <range/v3/algorithm/for_each.hpp>

namespace {
enum class ExpandedSpringStatus { OneDamaged, GroupOfOperational };

/**
 * \brief
 *
 * \param groupInfo
 *
 * \return List. True being "1 damaged" and False being "a gap of operational"
 * (1 or more operational).
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

uint64_t Record::solve() const
{
    // add extra operational springs in both sides
    std::string springsStr{mSprings};
    springsStr.insert(0, ".");
    springsStr += '.';

    // TODO
}

} // namespace aoc_2023_12
