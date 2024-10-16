#include "FlipFlop.hpp"

namespace aoc_2023_20 {

namespace {

/**
 *
 * @param value
 * @return
 */
[[nodiscard]] SignalValue flip(SignalValue const value) noexcept
{
    return value == SignalValue::Low ? SignalValue::High : SignalValue::Low;
}

} // namespace

FlipFlop::FlipFlop(ModuleName const& name) noexcept
    : IModule(name)
{
}

std::vector<Signal> FlipFlop::process(Signal const& input) noexcept
{
    std::vector<Signal> output;
    if (input.value == SignalValue::Low) {
        /* update the last value */
        mLastValue = flip(mLastValue);
        /* generate output */
        output.reserve(mDestinations.size());
        for (auto const& destination : mDestinations) {
            output.emplace_back(mModuleName, destination, mLastValue);
        }
    }
    return output;
}

void FlipFlop::addDestination(ModuleName const& destination) noexcept
{
    mDestinations.push_back(destination);
}

} // namespace aoc_2023_20
