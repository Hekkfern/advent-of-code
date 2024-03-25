#include "Rocks.hpp"

#include <range/v3/view/drop.hpp>
#include <range/v3/view/stride.hpp>

namespace aoc_2023_14 {

Rocks::Rocks(
    std::vector<char>&& flattenGrid,
    std::size_t width,
    std::size_t height) noexcept
    : mFlattenGrid{std::move(flattenGrid)}
    , mWidth{width}
    , mHeight{height}
{
}

/**
 * @brief
 *
 * @param[in,out] rocks
 */
void Rocks::shift(auto rng)
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
        if (*src == 'O') {
            std::iter_swap(src, dst);
            // If its '#' shift dst
        } else if (*src == '#') {
            dst = src;
        }
    }
}

/**
 *
 * @param rocks
 */
void Rocks::shiftNorth() noexcept
{
    for (std::size_t colIndex{0ULL}; colIndex < mWidth; ++colIndex) {
        shift(
            mFlattenGrid | ranges::views::drop(colIndex)
            | ranges::views::stride(mWidth));
    }
}

/**
 * @brief
 * @param[in] rocks
 * @return
 */
uint64_t Rocks::calculateLoad() noexcept
{
    // TODO
}

} // namespace aoc_2023_14