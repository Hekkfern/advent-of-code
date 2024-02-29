#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2023_9 {

class History {
public:
    explicit History(std::vector<int64_t>&& seq) noexcept;
    [[nodiscard]] int64_t extrapolateRight() const noexcept;
    [[nodiscard]] int64_t extrapolateLeft() const noexcept;

private:
    std::vector<int64_t> mSequence;
};

} // namespace aoc_2023_9
