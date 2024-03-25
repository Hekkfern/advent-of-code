#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2023_14 {

class Rocks {
public:
    Rocks(
        std::vector<char>&& flattenGrid,
        std::size_t width,
        std::size_t height) noexcept;
    void shiftNorth() noexcept;
    [[nodiscard]] uint64_t calculateLoad() noexcept;

private:
    void shift(auto rng);

    std::vector<char> mFlattenGrid;
    std::size_t mWidth;
    std::size_t mHeight;
};

} // namespace aoc_2023_14
