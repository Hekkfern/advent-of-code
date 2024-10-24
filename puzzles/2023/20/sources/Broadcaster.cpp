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
    std::vector<Signal> output;
    output.reserve(mDestinations.size());
    for (auto const& destination : mDestinations) {
        output.emplace_back(mModuleName, destination, input.value);
    }
    return output;
}

} // namespace aoc_2023_20
