#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(const std::string_view name, const uint32_t flowRate)
    : mName{ name }
    , mFlowRate{ flowRate }
{
}

bool Valve::isOpen() const { return mIsOpen; }

void Valve::open() { mIsOpen = true; }

uint32_t Valve::getFlowRate() const { return mFlowRate; }

const std::string& Valve::getName() const { return mName; }

std::vector<std::pair<std::reference_wrapper<Valve>, uint32_t>>
Valve::getNeighbors() const
{
    return mNeighbors;
}

bool Valve::operator==(const Valve& other) const
{
    return mName == other.mName;
}

void Valve::addNeighbor(Valve& neighbor, uint32_t distance)
{
    mNeighbors.emplace_back(neighbor, distance);
}

} // namespace aoc_2022_16
