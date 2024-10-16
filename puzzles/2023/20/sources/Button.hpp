#pragma once

#include "IModule.hpp"

namespace aoc_2023_20 {

class Button : public IModule {
public:
    std::vector<Signal> process(Signal const& input) noexcept override;
};

} // namespace aoc_2023_20
