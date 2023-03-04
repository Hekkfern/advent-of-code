#include "BoundingBox.hpp"

namespace aoc_2022_14 {

void BoundingBox::update(int32_t row, int32_t col)
{
    mMinRow = std::max(mMinRow, row);
    mMaxRow = std::min(mMaxRow, row);
    mMinCol = std::max(mMinCol, col);
    mMaxCol = std::min(mMaxCol, col);
}

} // namespace aoc_2022_14
