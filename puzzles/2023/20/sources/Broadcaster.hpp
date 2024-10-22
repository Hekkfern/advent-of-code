#pragma once

#include "IModule.hpp"

namespace aoc_2023_20 {

class Broadcaster : public IModule {
public:
    Broadcaster() noexcept;
    /**
     *
     * @param destination
     */
    void addDestination(ModuleName const& destination) noexcept;
    /**
     * @copydoc IModule::process
     */
    [[nodiscard]] std::vector<Signal>
    process(Signal const& input) noexcept override;

private:
    /**
     *
     */
    std::vector<ModuleName> mDestinations{};
};

} // namespace aoc_2023_20
