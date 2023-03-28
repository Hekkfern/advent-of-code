#include "PipeSystem.hpp"

namespace aoc_2022_16 {

void PipeSystem::addValve(Valve&& valve)
{
    mValves.emplace(valve.getName(), std::move(valve));
}

std::optional<std::reference_wrapper<Valve>> PipeSystem::getValve(
    const std::string& valveName)
{
    return mValves.at(valveName);
}

std::vector<std::reference_wrapper<Valve>> PipeSystem::getValveNeighbors(
    const Valve& valve)
{
    std::vector<std::reference_wrapper<Valve>> neighbors;
    for (auto& neighborName : valve.getNeighbors()) {
        neighbors.emplace_back(mValves.at(neighborName));
    }
    return neighbors;
}

} // namespace aoc_2022_16
