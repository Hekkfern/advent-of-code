#pragma once

#include "Coordinate2D.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/join.hpp>
#include <utils/Math.hpp>

namespace utils::geometry2d {

/**
 * @brief      A 2D grid of values that repeats the base grid infinitely in
 *             every direction in 2D spaces.
 *
 * @tparam     T     The type of the values in the grid.
 */
template <typename T>
class InfiniteGrid2D {
public:
    using Coord = Coordinate2D<int64_t>;
    /**
     * @brief      Constructs a new instance.
     */
    InfiniteGrid2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  grid  The grid in 2D format.
     */
    explicit InfiniteGrid2D(std::vector<std::vector<T>> const& grid) noexcept
    {
        if (!grid.empty()) {
            mFlatGrid = grid | ranges::views::join | ranges::to<std::vector>;
            mWidth = grid[0].size();
            mHeight = grid.size();
        }
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(InfiniteGrid2D const& other) const noexcept
    {
        return mWidth == other.mWidth && mHeight == other.mHeight
            && mFlatGrid == other.mFlatGrid;
    }
    /**
     * @brief      Accesses the element at the specified row and column.
     *
     * @note       It's the caller's responsibility to ensure the indices are
     *             within the bounds of the grid.
     *
     * @param[in]  row   The row index.
     * @param[in]  col   The column index.
     *
     * @return     A reference to the element at the specified position.
     *
     * @{
     */
    [[nodiscard]] T& at(int64_t const row, int64_t const col) noexcept
    {
        return mFlatGrid[row * mWidth + col];
    }
    [[nodiscard]] T const&
    at(int64_t const row, int64_t const col) const noexcept
    {
        return mFlatGrid[row * mWidth + col];
    }
    /** }@ */
    /**
     * @brief      Accesses the element at the specified row and column.
     *
     * @note       It's the caller's responsibility to ensure the indices are
     *             within the bounds of the grid.
     *
     * @param[in]  coords   The coords of the matrix.
     *
     * @return     A reference to the element at the specified position.
     *
     * @{
     */
    [[nodiscard]] T& at(Coord const& coords) noexcept
    {
        auto const x{static_cast<std::size_t>(
            utils::math::modulusFloor<int64_t>(coords.getX(), mWidth))};
        auto const y{static_cast<std::size_t>(
            utils::math::modulusFloor<int64_t>(coords.getY(), mHeight))};
        return mFlatGrid[y * mWidth + x];
    }
    [[nodiscard]] T const& at(Coord const& coords) const noexcept
    {
        return at(coords);
    }
    [[nodiscard]] T& at(Coord&& coords) noexcept { return at(coords); }
    [[nodiscard]] T const& at(Coord&& coords) const noexcept
    {
        return at(coords);
    }
    /** }@ */
    /**
     * @brief      Moves a position in the grid according to a given direction.
     *
     * @param[in]  position   The current position.
     * @param[in]  direction  The direction to move.
     *
     * @return     The new position after moving in the given direction, or
     * std::nullopt if the movement is not possible.
     */
    [[nodiscard]] constexpr std::optional<Coord>
    move(Coord const& position, Direction2D const& direction) const noexcept
    {
        auto const result{position.move(direction)};
        if (!result) {
            return std::nullopt;
        }
        return *result;
    }
    /**
     * @brief     Gets all the valid neighbors (in the four main directions) of
     * a given position in the grid.
     *
     * @param[in] position The position to get the neighbors of.
     *
     * @return List of valid positions.
     */
    [[nodiscard]] std::vector<Coord>
    getCardinalNeighbors(Coord const& position) const noexcept
    {
        std::vector<Coord> neighbors;
        for (auto const direction : Direction2D::cardinalAll()) {
            auto const newPosition{move(position, direction)};
            if (newPosition) {
                neighbors.push_back(*newPosition);
            }
        }
        return neighbors;
    }

private:
    /**
     * Flat representation of the 2D grid of rocks.
     *
     * @details    Rows are concatenated one after another.
     */
    std::vector<T> mFlatGrid{};
    /**
     * The width of the grid.
     */
    std::size_t mWidth{0ULL};
    /**
     * The height of the grid.
     */
    std::size_t mHeight{0ULL};
};

} // namespace utils::geometry2d
