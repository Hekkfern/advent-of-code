#include "PipeSystem.hpp"

namespace aoc_2022_16 {

void PipeSystem::addValve(Valve&& valve)
{
    mValves.emplace(valve.getName(), std::move(valve));
}

Valve& PipeSystem::getValve(const std::string& valveName)
{
    return mValves.at(valveName);
}

} // namespace aoc_2022_16
