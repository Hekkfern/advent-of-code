#include "Pattern.hpp"

#include <cassert>
#include <range/v3/view/iota.hpp>

namespace aoc_2023_13 {

Pattern::Pattern(std::vector<std::string>&& data) noexcept
    : mData{std::move(data)}
{
}

std::vector<std::pair<std::size_t, std::size_t>>
Pattern::searchHorizontalReflectionLines() const noexcept
{
    std::size_t const height{mData.size()};
    std::vector<std::pair<std::size_t, std::size_t>> results;
    for (std::size_t rowIndex{1ULL}; rowIndex < height - 1ULL; ++rowIndex) {
        // check if this column and the one to the right are equal
        if (!areRowsEqual(rowIndex, rowIndex + 1ULL)) {
            continue;
        }
        // it is a candidate to reflection line
        // let's compare the next lines
        std::size_t rowIndex1{rowIndex - 1ULL};
        std::size_t rowIndex2{rowIndex + 2ULL};
        bool isDifferenceFound{false};
        while (!isDifferenceFound && rowIndex1 > 0ULL && rowIndex2 < height) {
            if (!areRowsEqual(rowIndex, rowIndex + 1ULL)) {
                isDifferenceFound = true;
            }
            --rowIndex1;
            ++rowIndex2;
        }
        if (isDifferenceFound) {
            continue;
        }
        results.emplace_back(rowIndex, rowIndex + 1ULL);
    }
    return results;
}

std::vector<std::pair<std::size_t, std::size_t>>
Pattern::searchVerticalReflectionLines() const noexcept
{
    std::size_t const width{mData[0].size()};
    std::vector<std::pair<std::size_t, std::size_t>> results;
    for (std::size_t colIndex{1ULL}; colIndex < width - 1ULL; ++colIndex) {
        // check if this column and the one to the right are equal
        if (!areColumnsEqual(colIndex, colIndex + 1ULL)) {
            continue;
        }
        // it is a candidate to reflection line
        // let's compare the next lines
        std::size_t colIndex1{colIndex - 1ULL};
        std::size_t colIndex2{colIndex + 2ULL};
        bool isDifferenceFound{false};
        while (!isDifferenceFound && colIndex1 > 0ULL && colIndex2 < width) {
            if (!areColumnsEqual(colIndex, colIndex + 1ULL)) {
                isDifferenceFound = true;
            }
            --colIndex1;
            ++colIndex2;
        }
        if (isDifferenceFound) {
            continue;
        }
        results.emplace_back(colIndex, colIndex + 1ULL);
    }
    return results;
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
