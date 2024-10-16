#include "Conjunction.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <utility>

namespace aoc_2023_20 {

Conjunction::Conjunction(ModuleName name) noexcept
    : IModule{std::move(name)}
{
}

std::vector<Signal> Conjunction::process(Signal const& input) noexcept
{
    /* update the last value for the input */
    mLastValues[input.origin] = input.value;
    /* generate output */
    std::vector<Signal> output;
    if (ranges::all_of(
            mLastValues,
            [](std::pair<ModuleName, SignalValue> const& item) -> bool {
                return item.second == SignalValue::High;
            })) {
        // TODO
    } else {
        // TODO
    }
    return output;
}

void Conjunction::addDestination(ModuleName destination) noexcept
{
    mDestinations.push_back(std::move(destination));
}

} // namespace aoc_2023_20