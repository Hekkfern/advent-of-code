#pragma once

#include "IModule.hpp"
#include "Signal.hpp"
#include "Types.hpp"

namespace aoc_2023_20 {

class FlipFlop : public IModule {
public:
    /**
     *
     * @param name
     * @param destination
     */
    explicit FlipFlop(ModuleName name) noexcept;
    /**
     *
     * @param destination
     */
    void addDestination(ModuleName destination) noexcept override;
    /**
     * @copydoc IModule::process
     */
    std::vector<Signal> process(Signal const& input) noexcept override;

private:
    /**
     *
     */
    SignalValue mLastValue{SignalValue::Low};
    /**
     *
     */
    std::vector<ModuleName> mDestinations{};
};

} // namespace aoc_2023_20
