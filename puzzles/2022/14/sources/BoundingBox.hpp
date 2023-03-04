#pragma once

#include <algorithm>
#include <cstdint>

namespace aoc_2022_14 {

class BoundingBox {
public:
    void update(int32_t row, int32_t col);

private:
    int32_t mMinRow{ 1'000 };
    int32_t mMaxRow{ -1 };
    int32_t mMinCol{ 1'000 };
    int32_t mMaxCol{ -1 };
};

} // namespace aoc_2022_14
