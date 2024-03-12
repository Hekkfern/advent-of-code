#pragma once

#include <functional>
#include <string>
#include <vector>

namespace aoc_2023_13 {

class Pattern {
public:
    /**
     * @brief Constructs an instance.
     *
     * @param[in] data Data
     */
    explicit Pattern(std::vector<std::string>&& data) noexcept;
    /**
     * @brief
     *
     * @return
     */
    [[nodiscard]] std::vector<std::size_t>
    searchHorizontalReflectionLines() const noexcept;
    /**
     * @brief
     *
     * @return
     */
    [[nodiscard]] std::vector<std::size_t>
    searchVerticalReflectionLines() const noexcept;

private:
    /**
     * @brief
     * @param rowIndex
     * @param predicate
     */
    void forEachItemInRow(
        std::size_t rowIndex, std::function<void(char const c)>&& predicate);
    /**
     * @brief
     *
     * @param colIndex
     * @param predicate
     */
    void forEachItemInColumn(
        std::size_t colIndex, std::function<void(char const c)>&& predicate);

    std::vector<std::string> mData;
};

} // namespace aoc_2023_13
