#include "Pattern.hpp"

#include <range/v3/view/iota.hpp>

namespace {
std::optional<std::pair<std::size_t, std::size_t>>
mirror(std::vector<uint64_t> const& rng)
{
    std::size_t const size{rng.size()};
    std::pair<std::size_t, std::size_t> result;
    for (std::size_t const index : ranges::views::iota(0ULL, size - 1ULL)) {
        // check if this column and the one to the right are equal
        std::size_t const nextIndex{index + 1ULL};
        if (rng[index] != rng[nextIndex]) {
            continue;
        }
        // it is a candidate to reflection line
        // let's compare the next lines
        int64_t leftIndex{static_cast<int64_t>(index) - 1LL};
        std::size_t rightIndex{nextIndex + 1ULL};
        bool isDifferenceFound{false};
        while (!isDifferenceFound && leftIndex >= 0LL && rightIndex < size) {
            if (rng[leftIndex] != rng[rightIndex]) {
                isDifferenceFound = true;
            }
            --leftIndex;
            ++rightIndex;
        }
        if (isDifferenceFound) {
            continue;
        }
        return std::make_pair(index, nextIndex);
    }
    return {};
}

} // namespace

namespace aoc_2023_13 {

Pattern::Pattern(
    std::vector<uint64_t>&& rows, std::vector<uint64_t>&& cols) noexcept
    : mRowsData{std::move(rows)}
    , mColumnsData{std::move(cols)}
{
}

std::optional<std::pair<std::size_t, std::size_t>>
Pattern::searchHorizontalReflectionLine() const noexcept
{
    return mirror(mRowsData);
}

std::optional<std::pair<std::size_t, std::size_t>>
Pattern::searchVerticalReflectionLine() const noexcept
{
    return mirror(mColumnsData);
}

} // namespace aoc_2023_13
