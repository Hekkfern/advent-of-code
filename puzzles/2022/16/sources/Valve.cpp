#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(
    std::string_view name,
    uint32_t flowRate,
    std::vector<std::string>&& neighbours)
    : mName{ name }
    , mFlowRate{ flowRate }
    , mNeighbourValves{ std::move(neighbours) }
{
}

bool Valve::isOpen() const { return mIsOpen; }

void Valve::open()
{
    // TODO
}

uint32_t Valve::getFlowRate() const { return mFlowRate; }

} // namespace aoc_2022_16
