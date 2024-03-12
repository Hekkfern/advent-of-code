#include "Pattern.hpp"

#include <range/v3/view/iota.hpp>

namespace aoc_2023_13 {

Pattern::Pattern(std::vector<std::string>&& data) noexcept
    : mData{data}
{
}

std::vector<std::size_t> Pattern::searchHorizontalReflectionLines() const noexcept
{
    // TODO
    return std::vector<std::size_t>();
}

std::vector<std::size_t> Pattern::searchVerticalReflectionLines() const noexcept
{
    //TODO
}

void Pattern::forEachItemInRow(
    std::size_t rowIndex, std::function<void(char const c)>&& predicate)
{
    std::size_t const width{mData[rowIndex].size()};
    for (std::size_t colIndex{0ULL}; colIndex < width; ++colIndex) {
        predicate(mData[rowIndex][colIndex]);
    }
}

void Pattern::forEachItemInColumn(
    std::size_t colIndex, std::function<void(char const c)>&& predicate)
{
    std::size_t const height{mData.size()};
    for (std::size_t rowIndex{0ULL}; rowIndex < height; ++rowIndex) {
        predicate(mData[rowIndex][colIndex]);
    }
}

} // namespace aoc_2023_13
