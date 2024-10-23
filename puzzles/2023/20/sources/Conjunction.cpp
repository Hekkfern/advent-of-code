#include "Conjunction.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/map.hpp>

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
    bool const allHigh{ranges::all_of(
        mLastValues | ranges::views::values, [](SignalValue const sig) -> bool {
            return sig == SignalValue::High;
        })};
    for (auto const& destination : mDestinations) {
        output.emplace_back(
            getModuleName(),
            destination,
            allHigh ? SignalValue::Low : SignalValue::High);
    }
    return output;
}

void Conjunction::addInput(ModuleName const& input) noexcept
{
    if (not mLastValues.contains(input)) {
        mLastValues.emplace(input, SignalValue::Low);
    }
}

} // namespace aoc_2023_20