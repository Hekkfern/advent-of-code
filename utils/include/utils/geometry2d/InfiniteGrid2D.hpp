#pragma once

#include "Grid2D.hpp"

namespace utils::geometry2d {

/**
 * @brief      A 2D grid of values. The coordinates are 0-based.
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
    explicit InfiniteGrid2D(Grid2D<T>& grid) noexcept
        : mGrid{grid}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  grid  The grid in 2D format.
     */
    explicit InfiniteGrid2D(Grid2D<T>&& grid) noexcept
        : mGrid{std::move(grid)}
    {
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
        return mGrid == other.mGrid;
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
        return mGrid.at(row, col);
    }
    [[nodiscard]] T const&
    at(int64_t const row, int64_t const col) const noexcept
    {
        return mGrid.at(row, col);
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
        return mGrid.at(coords.getY(), coords.getX());
    }
    [[nodiscard]] T const& at(Coord const& coords) const noexcept
    {
        return mGrid.at(coords.getY(), coords.getX());
    }
    [[nodiscard]] T& at(Coord&& coords) noexcept
    {
        return mGrid.at(coords.getY(), coords.getX());
    }
    [[nodiscard]] T const& at(Coord&& coords) const noexcept
    {
        return mGrid.at(coords.getY(), coords.getX());
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
        // TODO
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
        // TODO
    }

private:
    Grid2D<T> mGrid;
};

} // namespace utils::geometry2d
