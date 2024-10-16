#pragma once

#include "Types.hpp"
#include <utility>

namespace aoc_2023_20 {

struct Signal {
    Signal(
        ModuleName origin, ModuleName destination, SignalValue value) noexcept
        : origin(std::move(origin))
        , destination(std::move(destination))
        , value(value)
    {
    }

    ModuleName origin;
    ModuleName destination;
    SignalValue value;
};

} // namespace aoc_2023_20
