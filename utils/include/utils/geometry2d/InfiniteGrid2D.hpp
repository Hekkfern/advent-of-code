#pragma once

#include "Direction2D.hpp"
#include "Operations2D.hpp"
#include "Point2D.hpp"
#include <range/v3/algorithm/swap_ranges.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/join.hpp>
#include <utils/Math.hpp>

namespace utils::geometry2d {

/**
 * @brief      A 2D grid of values that repeats the base grid infinitely in
 *             every direction in 2D spaces.
 *
 * @tparam     ValueType     The type of the values in the grid.
 * @tparam     CoordinateType     Type of the coordinate values.
 */
template <typename ValueType, SignedIntegerType CoordinateType = int32_t>
class InfiniteGrid2D {
public:
    using CoordType = CoordinateType;
    using Coord = Point2D<CoordType>;
    /**
     * @brief      Constructs a new instance.
     */
    InfiniteGrid2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  grid  The grid in 2D format.
     */
    explicit InfiniteGrid2D(
        std::vector<std::vector<ValueType>> const& grid) noexcept
    {
        if (!grid.empty()) {
            mFlatGrid = grid | ranges::views::join | ranges::to<std::vector>;
            mWidth = grid[0].size();
            mHeight = grid.size();
        }
    }
    /**
     * @brief      Gets the width of the base grid.
     *
     * @return     The width.
     */
    [[nodiscard]] std::size_t getBaseWidth() const noexcept { return mWidth; }
    /**
     * @brief      Gets the height of the base grid.
     *
     * @return     The height.
     */
    [[nodiscard]] std::size_t getBaseHeight() const noexcept { return mHeight; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(InfiniteGrid2D const& other) const noexcept
        = default;
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
    [[nodiscard]] ValueType& at(int64_t const row, int64_t const col) noexcept
    {
        auto const clampedCoords{clampCoordinates(Coord{col, row})};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
    }
    [[nodiscard]] ValueType const&
    at(int64_t const row, int64_t const col) const noexcept
    {
        auto const clampedCoords{clampCoordinates(Coord{col, row})};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
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
    [[nodiscard]] ValueType& at(Coord const& coords) noexcept
    {
        auto const clampedCoords{clampCoordinates(coords)};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
    }
    [[nodiscard]] ValueType const& at(Coord const& coords) const noexcept
    {
        auto const clampedCoords{clampCoordinates(coords)};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
    }
    [[nodiscard]] ValueType& at(Coord&& coords) noexcept
    {
        auto const clampedCoords{clampCoordinates(coords)};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
    }
    [[nodiscard]] ValueType const& at(Coord&& coords) const noexcept
    {
        auto const clampedCoords{clampCoordinates(coords)};
        return mFlatGrid[clampedCoords.getY() * mWidth + clampedCoords.getX()];
    }
    /** }@ */
    /**
     * @brief      Flips the grid horizontally (i.e., invert columns).
     */
    void flipHorizontal() noexcept
    {
        for (auto row : ranges::views::iota(0ULL, mHeight)) {
            auto const rowStart{mFlatGrid.begin() + row * mWidth};
            auto const rowEnd{rowStart + mWidth};
            std::reverse(rowStart, rowEnd);
        }
    }
    /**
     * @brief      Flips the grid vertically (i.e., invert rows).
     */
    void flipVertical() noexcept
    {
        std::size_t const totalSwaps = mHeight / 2;

        for (std::size_t i{0ULL}; i < totalSwaps; ++i) {
            auto const topRowStart{std::next(mFlatGrid.begin(), i * mWidth)};
            auto const bottomRowStart{
                std::next(mFlatGrid.begin(), (mHeight - 1ULL - i) * mWidth)};
            ranges::swap_ranges(
                topRowStart, topRowStart + mWidth, bottomRowStart);
        }
    }
    /**
     * @brief      Rotates the grid 90 degrees clockwise.
     */
    void rotateClockwise() noexcept
    {
        std::vector<ValueType> rotatedGrid(mWidth * mHeight);
        for (std::size_t row{0ULL}; row < mHeight; ++row) {
            for (std::size_t col{0ULL}; col < mWidth; ++col) {
                rotatedGrid[col * mHeight + (mHeight - 1ULL - row)] = mFlatGrid
                    [row * mWidth + col];
            }
        }
        std::swap(mWidth, mHeight);
        mFlatGrid = std::move(rotatedGrid);
    }
    /**
     * @brief      Rotates the grid 90 degrees counterclockwise.
     */
    void rotateCounterClockwise() noexcept
    {
        std::vector<ValueType> rotatedGrid(mWidth * mHeight);
        for (std::size_t row{0ULL}; row < mHeight; ++row) {
            for (std::size_t col{0ULL}; col < mWidth; ++col) {
                rotatedGrid[(mWidth - 1ULL - col) * mHeight + row] = mFlatGrid
                    [row * mWidth + col];
            }
        }
        std::swap(mWidth, mHeight);
        mFlatGrid = std::move(rotatedGrid);
    }
    /**
     * @brief      Moves a position in the grid according to a given direction.
     *
     * @param[in]  position   The current position.
     * @param[in]  direction  The direction to move.
     *
     * @return     The new position after moving in the given direction, or
     *             std::nullopt if the movement is not possible.
     */
    [[nodiscard]] constexpr std::optional<Coord>
    move(Coord const& position, Direction2D const& direction) const noexcept
    {
        return utils::geometry2d::move(position, direction);
    }
    /**
     * @brief      Gets all the valid neighbors (in the four main directions) of
     *             a given position in the grid.
     *
     * @param[in]  position  The position to get the neighbors of.
     *
     * @return     List of valid positions.
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
     * @brief      Clamps the coordinates to the grid boundaries.
     *
     * @param[in]  coords  The coordinates to clamp.
     *
     * @return     The clamped coordinates.
     */
    [[nodiscard]] constexpr Coord
    clampCoordinates(Coord const& coords) const noexcept
    {
        return Coord{
            static_cast<int64_t>(
                utils::math::modulusFloor<int64_t>(coords.getX(), mWidth)),
            static_cast<int64_t>(
                utils::math::modulusFloor<int64_t>(coords.getY(), mHeight))};
    }

    /**
     * Flat representation of the 2D grid of rocks.
     *
     * @details    Rows are concatenated one after another.
     */
    std::vector<ValueType> mFlatGrid{};
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
