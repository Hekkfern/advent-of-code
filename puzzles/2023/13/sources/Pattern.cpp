#include "Pattern.hpp"

#include <cassert>
#include <range/v3/view/iota.hpp>

namespace aoc_2023_13 {

Pattern::Pattern(std::vector<std::string>&& data) noexcept
    : mData{data}
{
}

std::vector<std::size_t>
Pattern::searchHorizontalReflectionLines() const noexcept
{
    // TODO
    return std::vector<std::size_t>();
}

std::vector<std::size_t> Pattern::searchVerticalReflectionLines() const noexcept
{
    // TODO
}

void Pattern::forEachItemInRow(
    std::size_t const rowIndex,
    std::function<void(char const c)>&& predicate) const
{
    std::size_t const width{mData[rowIndex].size()};
    for (std::size_t colIndex{0ULL}; colIndex < width; ++colIndex) {
        predicate(mData[rowIndex][colIndex]);
    }
}

void Pattern::forEachItemInColumn(
    std::size_t const colIndex,
    std::function<void(char const c)>&& predicate) const
{
    std::size_t const height{mData.size()};
    for (std::size_t rowIndex{0ULL}; rowIndex < height; ++rowIndex) {
        predicate(mData[rowIndex][colIndex]);
    }
}

bool Pattern::areColumnsEqual(
    std::size_t const colIndex1, std::size_t const colIndex2) const
{
    assert(colIndex1 < mData[colIndex1].size());
    assert(colIndex2 < mData[colIndex2].size());
    assert(colIndex1 != colIndex2);

    std::size_t const height{mData.size()};
    for (std::size_t rowIndex{0ULL}; rowIndex < height; ++rowIndex) {
        if (mData[rowIndex][colIndex1] != mData[rowIndex][colIndex2]) {
            return false;
        }
    }
    return true;
}

bool Pattern::areRowsEqual(
    std::size_t const rowIndex1, std::size_t const rowIndex2) const
{
    assert(rowIndex1 < mData.size());
    assert(rowIndex2 < mData.size());
    assert(rowIndex1 != rowIndex2);

    std::size_t const width{mData[rowIndex1].size()};
    for (std::size_t colIndex{0ULL}; colIndex < width; ++colIndex) {
        if (mData[rowIndex1][colIndex] != mData[rowIndex2][colIndex]) {
            return false;
        }
    }
    return true;
}

} // namespace aoc_2023_13
