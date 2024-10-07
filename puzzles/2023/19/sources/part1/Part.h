#pragma once

#include <array>
#include <cstdint>

namespace aoc_2023_19::part1 {

struct Part {
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Category x value.
     * @param[in]  m     Category m value.
     * @param[in]  a     Category a value.
     * @param[in]  s     Category s value.
     */
    Part(uint32_t x, uint32_t m, uint32_t a, uint32_t s);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in] categories Category values.
     */
    explicit Part(std::array<uint32_t, 4> const& categories);
    /**
     * @brief      Sum of all the categories, for the final result.
     *
     * @return     Sum of all the categories.
     */
    [[nodiscard]] uint32_t sum() const noexcept;

    /**
     * @brief Category of the part.
     *
     * @{
     */
    uint32_t x;
    uint32_t m;
    uint32_t a;
    uint32_t s;
    /** @}*/
};

} // namespace aoc_2023_19
