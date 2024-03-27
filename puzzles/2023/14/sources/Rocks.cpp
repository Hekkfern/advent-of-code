#include "Rocks.hpp"

#include <algorithm>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/stride.hpp>

namespace {

/**
 * @brief      Shift all the rounded rocks from back to front.
 *
 * @param[in]  rng   The row or column of the grid.
 */
void shift(auto rng)
{
    // First available space to the left
    auto dst = rng.begin();
    // Currently examined space
    auto src = rng.begin();
    while (true) {
        // Jump to the next empty space
        while (dst != rng.end() && *dst != '.') {
            ++dst;
        }
        // No empty spaces, we are done
        if (dst == rng.end()) {
            break;
        }
        // We are shifting to the left, so our src has to be to the right of dst
        src = dst;
        // Find the next non-empty space
        while (src != rng.end() && *src == '.') {
            ++src;
        }
        // All empty spaces, we are done
        if (src == rng.end()) {
            break;
        }
        // If it is a 'O', shift it to dst
        // but if its '#', shift dst
        if (*src == 'O') {
            std::iter_swap(src, dst);
        } else if (*src == '#') {
            dst = src;
        }
    }
}

} // namespace

namespace aoc_2023_14 {

Rocks::Rocks(
    std::vector<char>&& flatGrid,
    std::size_t const width,
    std::size_t const height) noexcept
    : mFlatGrid{std::move(flatGrid)}
    , mWidth{width}
    , mHeight{height}
{
}

void Rocks::shiftNorth() noexcept
{
    for (std::size_t colIndex{0ULL}; colIndex < mWidth; ++colIndex) {
        shift(
            mFlatGrid | ranges::views::drop(colIndex)
            | ranges::views::stride(mWidth));
    }
}

uint64_t Rocks::calculateLoad() const noexcept
{
    uint64_t weight{0ULL};
    for (auto const [rowIndex, row] :
         mFlatGrid | ranges::views::chunk(mWidth) | ranges::views::enumerate) {
        weight += std::ranges::count(row, 'O') * (mHeight - rowIndex);
    }

    return weight;
}

} // namespace aoc_2023_14
