#pragma once

#include "IModule.hpp"

namespace aoc_2023_20 {

class Broadcaster : public IModule {
public:
    Broadcaster() noexcept;
    /**
     * @copydoc IModule::process
     */
    [[nodiscard]] std::vector<Signal>
    process(Signal const& input) noexcept override;
};

} // namespace aoc_2023_20
