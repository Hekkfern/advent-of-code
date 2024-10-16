#include "Part.hpp"

namespace aoc_2023_19::part1 {

Part::Part(
    uint32_t const x, uint32_t const m, uint32_t const a, uint32_t const s)
    : x{x}
    , m{m}
    , a{a}
    , s{s}
{
}
/**
 * @brief      Constructs a new instance.
 *
 * @param[in] categories Category values.
 */
Part::Part(std::array<uint32_t, 4> const& categories)
    : Part{categories[0], categories[1], categories[2], categories[3]}
{
}
/**
 * @brief      Sum of all the categories, for the final result.
 *
 * @return     Sum of all the categories.
 */
uint32_t Part::sum() const noexcept { return x + m + a + s; }

} // namespace aoc_2023_19::part1
