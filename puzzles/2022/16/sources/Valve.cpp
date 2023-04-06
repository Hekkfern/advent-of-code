#include "Valve.hpp"

namespace aoc_2022_16 {

Valve::Valve(const std::string_view name, const uint32_t flowRate)
    : mName{name}
    , mFlowRate{flowRate}
{
}

uint32_t Valve::getFlowRate() const { return mFlowRate; }

const std::string& Valve::getName() const { return mName; }

bool Valve::operator==(const Valve& other) const
{
    return mName == other.mName;
}

} // namespace aoc_2022_16
