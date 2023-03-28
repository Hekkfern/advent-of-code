#include "PressureTracker.hpp"

namespace aoc_2022_16 {

void PressureTracker::openValve(const uint32_t flowRate, const uint32_t time)
{
    constexpr uint32_t TotalTime{ 30U };
    mReleasedPressure += flowRate * (TotalTime - time);
}

uint32_t PressureTracker::getReleasedPressure() const
{
    return mReleasedPressure;
}

bool PressureTracker::operator==(const PressureTracker& other) const
{
    return mReleasedPressure == other.mReleasedPressure;
}

bool PressureTracker::operator<(const PressureTracker& other) const
{
    return mReleasedPressure < other.mReleasedPressure;
}

} // namespace aoc_2022_16
