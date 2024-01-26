#include "Schematic.hpp"

namespace aoc_2023_3 {

Part::Part(uint32_t const pn, utils::geometry2d::Line2D<> const& l)
    : partNumber{pn}
    , line{l}
{
}

Symbol::Symbol(char const c, utils::geometry2d::Point2D<> const& pos)
    : character{c}
    , position{pos}
{
}
bool Symbol::operator==(Symbol const& other) const
{
    return character == other.character && position == other.position;
}

void Schematic::merge(Schematic&& other) noexcept
{
    parts.reserve(parts.size() + other.parts.size());
    std::move(
        other.parts.begin(), other.parts.end(), std::back_inserter(parts));
    std::move(
        other.symbols.begin(),
        other.symbols.end(),
        std::back_inserter(symbols));
}

} // namespace aoc_2023_3
