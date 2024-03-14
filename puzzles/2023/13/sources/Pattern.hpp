#pragma once

#include <optional>
#include <vector>

namespace aoc_2023_13 {

class Pattern {
public:
    /**
     * @brief Constructs an instance.
     *
     * @param[in] data Data
     * @param[in] data Data
     */
    explicit Pattern(
        std::vector<uint64_t>&& rows, std::vector<uint64_t>&& cols) noexcept;
    /**
     * @brief
     *
     * @return
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchHorizontalReflectionLine() const noexcept;
    /**
     * @brief
     *
     * @return
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchVerticalReflectionLine() const noexcept;

private:
    std::vector<uint64_t> mRowsData;
    std::vector<uint64_t> mColumnsData;
};

} // namespace aoc_2023_13
