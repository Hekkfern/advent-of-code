#include "Broadcaster.hpp"

namespace aoc_2023_20 {

namespace {
constexpr auto BroadcasterName{"broadcaster"};
}

Broadcaster::Broadcaster() noexcept
    : IModule{BroadcasterName}
{
}

std::vector<Signal> Broadcaster::process(Signal const& input) noexcept
{
    std::vector<Signal> signals;
    signals.reserve(mDestinations.size());
    for (auto const& destination : mDestinations) {
        signals.emplace_back(mModuleName, destination, input.value);
    }
    return signals;
}

void Broadcaster::addDestination(ModuleName const& destination) noexcept
{
    mDestinations.push_back(destination);
}

} // namespace aoc_2023_20
