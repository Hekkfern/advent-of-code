#include "FlipFlop.hpp"

#include <utility>

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

FlipFlop::FlipFlop(ModuleName name) noexcept
    : IModule(std::move(name))
{
}

std::vector<Signal> FlipFlop::process(Signal const& input) noexcept
{
    std::vector<Signal> output;
    if (input.value == SignalValue::Low) {
        /* update the last value */
        mLastValue = flip(mLastValue);
        /* generate output */
        for (auto const& destination : mDestinations) {
            output.emplace_back(mModuleName, destination, mLastValue);
        }
    }
    return output;
}

void FlipFlop::addDestination(ModuleName destination) noexcept
{
    mDestinations.push_back(std::move(destination));
}

} // namespace aoc_2023_20
