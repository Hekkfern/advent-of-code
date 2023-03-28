#pragma once

#include "Valve.hpp"
#include <string_view>
#include <unordered_map>

namespace aoc_2022_16 {

class PipeSystem {
public:
    void addValve(Valve&& valve);
    Valve& getValve(const std::string& valveName);

private:
    std::unordered_map<std::string, Valve> mValves;
};

} // namespace aoc_2022_16
