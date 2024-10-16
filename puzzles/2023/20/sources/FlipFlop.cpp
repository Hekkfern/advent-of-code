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

FlipFlop::FlipFlop(ModuleName name, ModuleName destination) noexcept
    : IModule(std::move(name))
    , mDestination(std::move(destination))
{
}

std::vector<Signal> FlipFlop::process(Signal const& input) noexcept
{
    std::vector<Signal> output;
    if (input.value == SignalValue::Low) {
        mLastValue = flip(mLastValue);
        output.emplace_back(mDestination, mLastValue);
    }
    return output;
}

} // namespace aoc_2023_20
