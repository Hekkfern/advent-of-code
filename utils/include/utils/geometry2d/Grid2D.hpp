#pragma once

#include <functional>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>

namespace utils::geometry2d {

template <typename T>
class Grid2D {
public:
    /**
     * @brief      Constructs a new instance.
     */
    Grid2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  grid  The grid in 2D format.
     */
    explicit Grid2D(std::vector<std::vector<T>> const& grid) noexcept
        : mFlatGrid{grid | ranges::views::join | ranges::to<std::vector>}
        , mWidth{grid[0].size()}
        , mHeight{grid.size()}
    {
    }
    /**
     * @brief      Gets the values of the row with the specified index.
     *
     * @param[in]  rowIndex  The row index. Index starts with value 0.
     *
     * @return     The row values.
     */
    [[nodiscard]] std::vector<T>
    getRow(std::size_t const rowIndex) const noexcept
    {
        if (rowIndex >= mHeight) {
            return {};
        }
        return mFlatGrid | ranges::views::chunk(mWidth)
            | ranges::views::drop(rowIndex) | ranges::views::take(1)
            | ranges::views::join | ranges::to<std::vector<int>>;
    }
    /**
     * @brief      Gets the values of the column with the specified index.
     *
     * @param[in]  colIndex  The column index. Index starts with value 0.
     *
     * @return     The column values.
     */
    [[nodiscard]] std::vector<T>
    getColumn(std::size_t const colIndex) const noexcept
    {
        if (colIndex >= mWidth) {
            return {};
        }
        return mFlatGrid | ranges::views::drop(colIndex)
            | ranges::views::stride(mWidth) | ranges::views::take(mWidth + 1)
            | ranges::to<std::vector<int>>;
    }
    /**
     * @brief      Gets the width.
     *
     * @return     The width.
     */
    [[nodiscard]] std::size_t getWidth() const noexcept { return mWidth; }
    /**
     * @brief      Gets the height.
     *
     * @return     The height.
     */
    [[nodiscard]] std::size_t getHeight() const noexcept { return mHeight; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool operator==(Grid2D const& other) const noexcept
    {
        return mWidth == other.mWidth && mHeight == other.mHeight
            && mFlatGrid == other.mFlatGrid;
    }
    /**
     * @brief      Iterates over each item in the specified row.
     *
     * @param[in]  rowIndex  The row index. Index starts with value 0.
     * @param[in]  callback  The callback function to call for each item. The
     *                       callback function should return true to continue
     *                       iterating, or false to cancel it.
     */
    void iterateRow(
        std::size_t rowIndex,
        std::function<bool(T const& item)> callback) const noexcept
    {
        if (rowIndex >= mHeight) {
            return;
        }

        auto const start = rowIndex * mWidth;
        auto const end = start + mWidth;

        auto rowItems
            = ranges::views::iota(start, end)
            | ranges::views::transform([this](std::size_t const flatIndex) {
                  return mFlatGrid[flatIndex];
              });

        for (auto item : rowItems) {
            if (!callback(item)) {
                break; // Cancel the iteration if callback returns false
            }
        }
    }
    /**
     * @brief      Iterates over each item in the specified column.
     *
     * @param[in]  colIndex  The column index. Index starts with value 0.
     * @param[in]  callback  The callback function to call for each item. The
     *                       callback function should return true to continue
     *                       iterating, or false to cancel it.
     */
    void iterateColumn(
        std::size_t colIndex,
        std::function<bool(T const& item)> callback) const noexcept
    {
        if (colIndex >= mWidth) {
            return; // Invalid column index
        }

        auto columnItems
            = ranges::views::iota(0ULL, mHeight)
            | ranges::views::
                transform([this, colIndex](std::size_t const rowIndex) {
                    return mFlatGrid[rowIndex * mWidth + colIndex];
                });

        for (auto item : columnItems) {
            if (!callback(item)) {
                break; // Cancel the iteration if callback returns false
            }
        }
    }

private:
    /**
     * Flat representation of the 2D grid of rocks.
     *
     * @details    Rows are concatenated one after another.
     */
    std::vector<T> mFlatGrid{};
    /**
     * The width of the grid.
     */
    std::size_t mWidth{0ULL};
    /**
     * The height of the grid.
     */
    std::size_t mHeight{0ULL};
};

} // namespace utils::geometry2d
