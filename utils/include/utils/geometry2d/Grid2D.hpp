#pragma once

#include <algorithm>
#include <functional>
#include <optional>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/swap_ranges.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/filter.hpp>
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
     *
     * @{
     */
    void iterateRow(
        std::size_t const rowIndex,
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

        for (auto const& item : rowItems) {
            if (!std::invoke(callback, item)) {
                break; // Cancel the iteration if callback returns false
            }
        }
    }
    void iterateRow(
        std::size_t const rowIndex,
        std::function<bool(T& item)> callback) noexcept
    {
        if (rowIndex >= mHeight) {
            return;
        }

        auto startIt = mFlatGrid.begin() + rowIndex * mWidth;
        auto endIt = startIt + mWidth;
        for (auto it = startIt; it != endIt; ++it) {
            if (!std::invoke(callback, *it)) {
                break;
            }
        }
    }
    /** }@ */
    /**
     * @brief      Iterates over each item in the specified column.
     *
     * @param[in]  colIndex  The column index. Index starts with value 0.
     * @param[in]  callback  The callback function to call for each item. The
     *                       callback function should return true to continue
     *                       iterating, or false to cancel it.
     *
     * @{
     */
    void iterateColumn(
        std::size_t colIndex,
        std::function<bool(T const& item)> callback) const noexcept
    {
        if (colIndex >= mWidth) {
            return;
        }

        auto columnItems
            = ranges::views::iota(0ULL, mHeight)
            | ranges::views::
                transform([this, colIndex](std::size_t const rowIndex) {
                    return mFlatGrid[rowIndex * mWidth + colIndex];
                });

        for (auto const& item : columnItems) {
            if (!std::invoke(callback, item)) {
                break; // Cancel the iteration if callback returns false
            }
        }
    }
    void iterateColumn(
        std::size_t colIndex, std::function<bool(T& item)> callback) noexcept
    {
        if (colIndex >= mWidth) {
            return;
        }

        for (std::size_t rowIndex{0ULL}; rowIndex < mHeight; ++rowIndex) {
            auto& item{mFlatGrid[rowIndex * mWidth + colIndex]};
            if (!std::invoke(callback, item)) {
                break;
            }
        }
    }
    /** }@ */
    /**
     * @brief      Accesses the element at the specified row and column.
     *
     * @note       It's the caller's responsibility to ensure the indices are
     *             within the bounds of the grid.
     *
     * @param[in]  row   The row index.
     * @param[in]  col   The column index.
     *
     * @return     A reference to the element at the specified position.
     *
     * @{
     */
    T& at(std::size_t const row, std::size_t const col) noexcept
    {
        return mFlatGrid[row * mWidth + col];
    }
    T const& at(std::size_t const row, std::size_t const col) const noexcept
    {
        return mFlatGrid[row * mWidth + col];
    }
    /** }@ */
    /**
     * @brief      Extracts a subgrid from the grid.
     *
     * @param[in]  startRow  The starting row index for the subgrid.
     * @param[in]  startCol  The starting column index for the subgrid.
     * @param[in]  numRows   The number of rows in the subgrid.
     * @param[in]  numCols   The number of columns in the subgrid.
     *
     * @return     A new Grid2D object representing the subgrid.
     */
    [[nodiscard]] Grid2D<T> subgrid(
        std::size_t const startRow,
        std::size_t const startCol,
        std::size_t const numRows,
        std::size_t const numCols) const noexcept
    {
        if (startRow + numRows > mHeight || startCol + numCols > mWidth) {
            return {};
        }

        auto rowIndices = ranges::views::iota(startRow, startRow + numRows);
        auto subRows
            = rowIndices
            | ranges::views::transform(
                  [this, startCol, numCols](std::size_t const rowIndex) {
                      auto const rowStart{
                          mFlatGrid.begin() + rowIndex * mWidth + startCol};
                      return std::vector<T>(rowStart, rowStart + numCols);
                  })
            | ranges::to<std::vector<std::vector<T>>>();
        return Grid2D<T>(subRows);
    }
    /**
     * @brief      Flips the grid horizontally.
     */
    void flipHorizontal() noexcept
    {
        for (auto row : ranges::views::iota(0ULL, mHeight)) {
            auto const rowStart{mFlatGrid.begin() + row * mWidth};
            auto const rowEnd{rowStart + mWidth};
            std::reverse(rowStart, rowEnd);
        }
    }
    /**
     * @brief      Flips the grid vertically.
     */
    void flipVertical() noexcept
    {
        std::size_t const totalSwaps = mHeight / 2;

        for (std::size_t i = 0; i < totalSwaps; ++i) {
            auto const topRowStart{mFlatGrid.begin() + i * mWidth};
            auto const bottomRowStart{
                mFlatGrid.begin() + (mHeight - 1 - i) * mWidth};
            ranges::swap_ranges(
                topRowStart, topRowStart + mWidth, bottomRowStart);
        }
    }
    /**
     * @brief      Rotates the grid 90 degrees clockwise.
     */
    void rotateClockwise() noexcept
    {
        std::vector<T> rotatedGrid(mWidth * mHeight);
        for (std::size_t row = 0; row < mHeight; ++row) {
            for (std::size_t col = 0; col < mWidth; ++col) {
                rotatedGrid[col * mHeight + (mHeight - 1 - row)] = mFlatGrid
                    [row * mWidth + col];
            }
        }
        std::swap(mWidth, mHeight);
        mFlatGrid = std::move(rotatedGrid);
    }
    /**
     * @brief      Rotates the grid 90 degrees counterclockwise.
     */
    void rotateCounterClockwise() noexcept
    {
        std::vector<T> rotatedGrid(mWidth * mHeight);
        for (std::size_t row = 0; row < mHeight; ++row) {
            for (std::size_t col = 0; col < mWidth; ++col) {
                rotatedGrid[(mWidth - 1 - col) * mHeight + row] = mFlatGrid
                    [row * mWidth + col];
            }
        }
        std::swap(mWidth, mHeight);
        mFlatGrid = std::move(rotatedGrid);
    }
    /**
     * @brief      Finds the first occurrence of a value in the grid.
     *
     * @param[in]  value  The value to search for.
     *
     * @return     An optional pair of indices (row, col) if the value is found,
     *             std::nullopt otherwise.
     */
    std::optional<std::pair<std::size_t, std::size_t>>
    findFirst(T const& value) const noexcept
    {
        auto const it = ranges::find_if(
            mFlatGrid, [&value = std::as_const(value)](T const& item) {
                return item == value;
            });

        if (it != mFlatGrid.end()) {
            std::size_t const index = std::distance(mFlatGrid.begin(), it);
            return std::make_pair(index % mWidth, index / mWidth);
        }
        return {};
    }
    /**
     * @brief      Finds all occurrences of a value in the grid.
     *
     * @param[in]  value  The value to search for.
     *
     * @return     A vector of pairs of indices (row, col) for each occurrence
     *             of the value.
     */
    std::vector<std::pair<std::size_t, std::size_t>>
    findAll(T const& value) const noexcept
    {
        return mFlatGrid | ranges::views::enumerate
            | ranges::views::filter([&value](auto const& pair) {
                   return pair.second == value;
               })
            | ranges::views::transform([this](auto const& pair) {
                   std::size_t index = pair.first;
                   return std::make_pair(index % mWidth, index / mWidth);
               })
            | ranges::to<std::vector<std::pair<std::size_t, std::size_t>>>();
    }
    /**
     * @brief      Resizes the grid to a new width and height, filling new
     *             spaces with a default value.
     *
     * @param[in]  newHeight     The new height of the grid.
     * @param[in]  newWidth      The new width of the grid.
     * @param[in]  defaultValue  The value to fill new cells with. Defaults to
     *                           T{}.
     */
    void resize(
        std::size_t const newHeight,
        std::size_t const newWidth,
        T const& defaultValue = T{}) noexcept
    {
        std::vector<T> newFlatGrid(newHeight * newWidth, defaultValue);

        for (std::size_t row = 0; row < std::min(newHeight, mHeight); ++row) {
            for (std::size_t col = 0; col < std::min(newWidth, mWidth); ++col) {
                newFlatGrid[row * newWidth + col] = mFlatGrid
                    [row * mWidth + col];
            }
        }

        mFlatGrid = std::move(newFlatGrid);
        mWidth = newWidth;
        mHeight = newHeight;
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
