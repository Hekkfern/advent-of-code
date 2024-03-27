#pragma once

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/stride.hpp>
#include <vector>

namespace utils::geometry2d {

template <typename T>
class Grid2D {
public:
    /**
     * \brief
     */
    Grid2D() noexcept = default;
    /**
     * \brief
     * \param[in] grid
     */
    explicit Grid2D(std::vector<std::vector<T>> const& grid) noexcept
        : mFlatGrid{grid | ranges::views::join | ranges::to<std::vector>}
        , mWidth{grid[0].size()}
        , mHeight{grid.size()}
    {
    }
    /**
     * \brief
     * \param[in] rowIndex
     * \return
     */
    [[nodiscard]] std::vector<T>
    getRow(std::size_t const rowIndex) const noexcept
    {
        return mFlatGrid | ranges::views::chunk(mWidth)
            | ranges::views::drop(rowIndex) | ranges::views::take(1)
            | ranges::to<std::vector>;
    }
    /**
     * \brief
     * \param[in] colIndex
     * \return
     */
    [[nodiscard]] std::vector<T>
    getColumn(std::size_t const colIndex) const noexcept
    {
        return mFlatGrid | ranges::views::drop(colIndex)
            | ranges::views::stride(mWidth) | ranges::views::take(1)
            | ranges::to<std::vector>;
    }
    /**
     * \brief
     * \return
     */
    [[nodiscard]] std::size_t getWidth() const noexcept { return mWidth; }
    /**
     * \brief
     * \return
     */
    [[nodiscard]] std::size_t getHeight() const noexcept { return mHeight; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool operator==(Grid2D const& other) const noexcept
    {
        return mWidth == other.mWidth && mHeight == other.mHeight
            && mFlatGrid == other.mFlatGrid;
    }

private:
    std::vector<T> mFlatGrid{};
    std::size_t mWidth{0ULL};
    std::size_t mHeight{0ULL};
};

} // namespace utils::geometry2d
