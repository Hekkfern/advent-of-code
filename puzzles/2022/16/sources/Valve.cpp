#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(std::string_view const name, uint32_t const flowRate)
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
