#pragma once

#include "Valve.hpp"
#include <optional>
#include <string_view>
#include <unordered_map>

namespace aoc_2022_16 {

class PipeSystem {
public:
    void addValve(Valve&& valve);
    std::optional<std::reference_wrapper<Valve>> getValve(
        const std::string& valveName);
    std::vector<std::reference_wrapper<Valve>> getValveNeighbors(
        const Valve& valve);

private:
    std::unordered_map<std::string, Valve> mValves{};
};

} // namespace aoc_2022_16
