#pragma once

#include <cstdint>
#include <vector>

namespace aoc_2023_14 {

class Rocks {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  flatGrid  The flattened grid
     * @param[in]  width     The width of the grid.
     * @param[in]  height    The height of the grid.
     */
    Rocks(
        std::vector<char>&& flatGrid,
        std::size_t width,
        std::size_t height) noexcept;
    /**
     * @brief      Shift all the rounded rocks to the north.
     */
    void shiftNorth() noexcept;
    /**
     * @brief      Calculates the load of all the rounded rocks.
     *
     * @details    The amount of load caused by a single rounded rock (O) is
     *             equal to the number of rows from the rock to the south edge
     *             of the platform, including the row the rock is on.
     *             (Cube-shaped rocks (#) don't contribute to load.)
     *
     * @return     The total load of all the rounded rocks.
     */
    [[nodiscard]] uint64_t calculateLoad() const noexcept;

private:
    /**
     * Flat representation of the 2D grid of rocks.
     *
     * @details    Rows are concatenated one after another.
     */
    std::vector<char> mFlattenGrid;
    /**
     * The width of the grid.
     */
    std::size_t mWidth;
    /**
     * The height of the grid.
     */
    std::size_t mHeight;
};

} // namespace aoc_2023_14
