#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(
    const std::string_view name,
    const uint32_t flowRate,
    std::vector<std::string>&& neighbors)
    : mName{ name }
    , mFlowRate{ flowRate }
    , mNeighbourValves{ std::move(neighbors) }
{
}

bool Valve::isOpen() const { return mIsOpen; }

void Valve::open() { mIsOpen = true; }

uint32_t Valve::getFlowRate() const { return mFlowRate; }

std::string_view Valve::getName() const { return mName; }

} // namespace aoc_2022_16
