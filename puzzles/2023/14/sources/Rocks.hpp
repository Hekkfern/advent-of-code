#pragma once

#include <cstdint>
#include <string>

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
        std::string&& flatGrid, std::size_t width, std::size_t height) noexcept;
    /**
     * @brief      Shift all the rounded rocks to the given direction.
     *
     * @{
     */
    void shiftNorth() noexcept;
    void shiftSouth() noexcept;
    void shiftWest() noexcept;
    void shiftEast() noexcept;
    /** }@ */
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
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(Rocks const& other) const noexcept
    {
        return mFlatGrid == other.mFlatGrid && mWidth == other.mWidth
            && mHeight == other.mHeight;
    }
    /**
     * Friend statement for the hash calculator
     */
    friend std::hash<Rocks>;

private:
    /**
     * Flat representation of the 2D grid of rocks.
     *
     * @details    Rows are concatenated one after another.
     */
    std::string mFlatGrid;
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

template <>
struct std::hash<aoc_2023_14::Rocks> {
    std::size_t operator()(aoc_2023_14::Rocks const& rocks) const noexcept
    {
        std::size_t result = 17;
        result = result * 31 + std::hash<std::string>()(rocks.mFlatGrid);
        result = result * 31 + std::hash<std::size_t>()(rocks.mWidth);
        result = result * 31 + std::hash<std::size_t>()(rocks.mHeight);
        return result;
    }
};
