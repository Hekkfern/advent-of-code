#include "Button.hpp"

namespace aoc_2023_20 {

namespace {
constexpr auto BroadcasterName{"broadcaster"};
}

std::vector<Signal> Button::process(Signal const&) noexcept
{
    return {{mModuleName, BroadcasterName, SignalValue::Low}};
}

} // namespace aoc_2023_20