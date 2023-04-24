#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(const std::string_view name, const uint32_t flowRate)
    : mName{name}
    , mFlowRate{flowRate}
{
}

uint32_t Valve::getFlowRate() const { return mFlowRate; }

std::string const& Valve::getName() const { return mName; }

bool Valve::operator==(Valve const& other) const
{
    return mName == other.mName;
}

} // namespace aoc_2022_16
