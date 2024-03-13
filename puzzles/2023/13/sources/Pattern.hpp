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
    [[nodiscard]] std::vector<std::pair<std::size_t, std::size_t>>
    searchHorizontalReflectionLines() const noexcept;
    /**
     * @brief
     *
     * @return
     */
    [[nodiscard]] std::vector<std::pair<std::size_t, std::size_t>>
    searchVerticalReflectionLines() const noexcept;

private:
    /**
     * @brief
     * @param rowIndex
     * @param predicate
     */
    void forEachItemInRow(
        std::size_t rowIndex, std::function<void(char c)>&& predicate) const;
    /**
     * @brief
     *
     * @param colIndex
     * @param predicate
     */
    void forEachItemInColumn(
        std::size_t colIndex, std::function<void(char c)>&& predicate) const;
    /**
     * \brief
     * \param colIndex1
     * \param colIndex2
     * \return
     */
    [[nodiscard]] bool
    areColumnsEqual(std::size_t colIndex1, std::size_t colIndex2) const;
    /**
     * \brief
     * \param rowIndex1
     * \param rowIndex2
     * \return
     */
    [[nodiscard]] bool
    areRowsEqual(std::size_t rowIndex1, std::size_t rowIndex2) const;

    std::vector<std::string> mData;
};

} // namespace aoc_2023_13
