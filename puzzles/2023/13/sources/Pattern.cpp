#include "Pattern.hpp"

#include <bit>
#include <numeric>
#include <ranges>
#include <span>

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

std::optional<std::pair<std::size_t, std::size_t>>
mirrorWithSingleFix(std::span<uint64_t const> const& rng)
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
        // Only proper splits
        if (prefix.empty() || suffix.empty()) {
            continue;
        }
        // Count the number of bit errors
        uint64_t bitcount{0LL};
        // inner_product uses the first range for length information,
        // we need to make sure that the first range is the shorter one
        if (prefix.size() >= suffix.size()) {
            bitcount = std::inner_product(
                suffix.begin(),
                suffix.end(),
                prefix.begin(),
                0ULL,
                std::plus<>{},
                [](uint64_t left, uint64_t right) {
                    // number of different bits
                    return std::popcount(left ^ right);
                });
        } else {
            bitcount = std::inner_product(
                prefix.begin(),
                prefix.end(),
                suffix.begin(),
                0ULL,
                std::plus<>{},
                [](uint64_t left, uint64_t right) {
                    // number of different bits
                    return std::popcount(left ^ right);
                });
        }
        // If we have exactly one bit error, we have our mirror line
        if (bitcount == 1) {
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

std::optional<std::pair<std::size_t, std::size_t>>
Pattern::searchHorizontalReflectionLineWithSingleFix() const noexcept
{
    return mirrorWithSingleFix(mRowsData);
}

std::optional<std::pair<std::size_t, std::size_t>>
Pattern::searchVerticalReflectionLineWithSingleFix() const noexcept
{
    return mirrorWithSingleFix(mColumnsData);
}

} // namespace aoc_2023_13
