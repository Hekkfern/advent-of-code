#include "Part.h"

namespace aoc_2023_19 {

Part::Part(uint32_t x, uint32_t m, uint32_t a, uint32_t s)
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

} // namespace aoc_2023_19
