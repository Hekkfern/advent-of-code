#include "Conjunction.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/map.hpp>
#include <utility>

namespace aoc_2023_20 {

Conjunction::Conjunction(ModuleName const& name) noexcept
    : IModule{name}
{
}

std::vector<Signal> Conjunction::process(Signal const& input) noexcept
{
    /* update the last value for the input */
    mLastValues[input.origin] = input.value;
    /* generate output */
    std::vector<Signal> output;
    output.reserve(mDestinations.size());
    if (ranges::all_of(
            mLastValues | ranges::views::values,
            [](SignalValue const sig) -> bool {
                return sig == SignalValue::High;
            })) {
        // TODO
    } else {
        // TODO
    }
    return output;
}

void Conjunction::addDestination(ModuleName const& destination) noexcept
{
    mDestinations.push_back(destination);
}

void Conjunction::addInput(ModuleName const& input) noexcept
{
    if (not mLastValues.contains(input)) {
        mLastValues.emplace(input, SignalValue::Low);
    }
}

} // namespace aoc_2023_20