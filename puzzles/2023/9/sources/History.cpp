#include "History.hpp"

#include <optional>
#include <range/v3/algorithm/all_of.hpp>

namespace {
std::vector<int64_t> calculateDifferences(std::vector<int64_t> const& input)
{
    if (input.size() < 2ULL) {
        return {}; // Return empty vector if input has less than 2 elements
    }
    std::vector<int64_t> differences;
    differences.reserve(input.size() - 1);
    for (std::size_t i{1ULL}; i < input.size(); ++i) {
        differences.emplace_back(input[i] - input[i - 1]);
    }
    return differences;
}

bool isAllZeros(std::vector<int64_t> const& input)
{
    return ranges::all_of(input, [](int64_t const item) -> bool {
        return item == 0ULL;
    });
}
} // namespace

namespace aoc_2023_9 {

History::History(std::vector<int64_t>&& seq) noexcept
    : mSequence{std::move(seq)}
{
}

std::optional<int64_t> extrapolateRecursive(std::vector<int64_t> const& input)
{
    auto const diffs{calculateDifferences(input)};
    if (isAllZeros(diffs)) {
        return {};
    }
    auto const nextLevel{extrapolateRecursive(diffs)};
    if (!nextLevel) {
        return diffs[0];
    }
    return diffs.back() + *nextLevel;
}

int64_t History::extrapolate() const noexcept
{
    auto const nextLevel{extrapolateRecursive(mSequence)};
    return mSequence.back() + *nextLevel;
}

} // namespace aoc_2023_9
