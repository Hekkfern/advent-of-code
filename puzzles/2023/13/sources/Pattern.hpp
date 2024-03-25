#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace aoc_2023_13 {

class Pattern {
public:
    /**
     * @brief      Constructs an instance.
     *
     * @param[in]  rows  Data of the rows.
     * @param[in]  cols  Data of the columns.
     */
    explicit Pattern(
        std::vector<uint64_t>&& rows, std::vector<uint64_t>&& cols) noexcept;
    /**
     * @brief      Looks for a mirror line in the rows.
     *
     * @return     If a mirror line is found, it returns a pair with the indexes
     *             of the rows before and after the mirror lane. Otherwise,
     *             std::nullopt.
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchHorizontalReflectionLine() const noexcept;
    /**
     * @brief      Looks for a mirror line in the columns.
     *
     * @return     If a mirror line is found, it returns a pair with the indexes
     *             of the rows before and after the mirror lane. Otherwise,
     *             std::nullopt.
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchVerticalReflectionLine() const noexcept;
    /**
     * @brief      Looks for a mirror line in the rows which it is discarded
     *             because it has a single error.
     *
     * @return     If a mirror line is found, it returns a pair with the indexes
     *             of the rows before and after the mirror lane. Otherwise,
     *             std::nullopt.
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchHorizontalReflectionLineWithSingleFix() const noexcept;
    /**
     * @brief      Looks for a mirror line in the columns which it is discarded
     *             because it has a single error.
     *
     * @return     If a mirror line is found, it returns a pair with the indexes
     *             of the rows before and after the mirror lane. Otherwise,
     *             std::nullopt.
     */
    [[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>>
    searchVerticalReflectionLineWithSingleFix() const noexcept;

private:
    /**
     * Stores the information of the rows of this pattern in binary format,
     * where '1' means '#' and '0' means '.'.
     */
    std::vector<uint64_t> mRowsData;
    /**
     * Stores the information of the rows of this pattern in binary format,
     * where '1' means '#' and '0' means '.'.
     */
    std::vector<uint64_t> mColumnsData;
};

} // namespace aoc_2023_13
