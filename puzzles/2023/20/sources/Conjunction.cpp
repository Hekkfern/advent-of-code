#include "Conjunction.hpp"

#include <utility>
#include <range/v3/algorithm/all_of.hpp>

namespace aoc_2023_20 {

Conjunction::Conjunction(ModuleName name) noexcept
    : IModule{std::move(name)}
{
}

std::vector<Signal> Conjunction::process(Signal const& input) noexcept
{
    mLastValues[input.destination] = input.value;
    if (ranges::all_of)
}

void Conjunction::addDestination(ModuleName destination) noexcept
{
    mLastValues.emplace(std::move(destination), SignalValue::Low);
}

} // namespace aoc_2023_20