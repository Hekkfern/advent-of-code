#include "Pattern.hpp"

#include <ranges>

namespace {
std::optional<std::pair<std::size_t, std::size_t>>
mirror(std::span<uint64_t const> const& rng)
{
    // All possible splits of the range into a prefix and a suffix
    // with the prefix reversed
    auto AllSplits
        = std::views::iota(rng.begin(), rng.end())
        | std::views::transform([&](auto it) {
              return std::pair{
                  std::ranges::subrange(rng.begin(), it) | std::views::reverse,
                  std::ranges::subrange(it, rng.end())};
          });
    for (auto [prefix, suffix] : AllSplits) {
        // We are looking for proper mirrors, both prefix and suffix
        // have to contain something
        if (prefix.empty() || suffix.empty()) {
            continue;
        }
        // Find the first mismatch
        auto const cmp = std::ranges::mismatch(prefix, suffix);
        // If there is no mismatch besides the length,
        // return the prefix size
        if (cmp.in1 == prefix.end() || cmp.in2 == suffix.end()) {
            return std::make_pair(prefix.size() - 1, prefix.size());
        }
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
